# ft_containers Методичка

## Содержание:
* [О чем проект?](#what_project?)
* [Немного о SFINAE](#SFINAE)
* [Категории выражений](#value_categories)
* [Итераторы](#Iterators)
  * [Названные требования(named requirements): LegacyIterator](#LegacyIterator)
  * [Иерархия и виды итераторов](#hierarchy_and_types_iterators)
  * [Шаблон iterator](#template_iterator)
  * [Iterator traits](#iterator_traits)
* [Обратный итератор](#reverse_iterator)
  * [Определение](#reverse_def)
  * [Типы параметров](#reverse_types)
  * [Поля](#reverse_fields)
  * [Методы](#reverse_methods)
      * [Конструктор](#reverse_constructor)
      * [operator =](#reverse_=)
      * [base](#reverse_base)
      * [operator \*](#reverse_star)
      * [operator ->](#reverse_arrow)
      * [operator []](#reverse_[])
      * [operator ++](#reverse_++)
      * [operator --](#reverse_--)
      * [operator ++(int)](#reverse_++_int)
      * [operator --(int)](#reverse_--_int)
      * [operator +](#reverse_+)
      * [operator -](#reverse_-)
      * [operator +=](#reverse_+=)
      * [operator -=](#reverse_-=)
  * [Функции, не являющиеся членами класса](#reverse_non_member)
      * [operator ==](#reverse_==)
      * [operator !=](#reverse_!=)
      * [operator <, <=, >, >=](#reverse_cmp)
      * [operator+(reverse_iterator)](#reverse_plus)
      * [operator-(reverse_iterator)](#reverse_minus)
  * [enable_if](#enable_if)
  * [integral_constant](#integral_constant)
  * [is_integral](#is_integral)
  * [lexicographical_compare](#lexicographical_compare)
  * [equal](#equal)  
  * [pair](#pair)
  * [make_pair](#make_pair)
  * [allcoator](#allcoator)
    * [Типы определенные в аллокаторе](#allocator_types)
    * [Конструкторы аллокатора](#allocator_constructors)
    * [Деструктор](#allocator_destructor)
    * [address](#allocator_address)
    * [deallocate](#deallocate)
    * [max_size](#allocator_max_size)
    * [construct](#construct)
    * [destroy](#destroy)
  * [Vector](#Vector)

## О чем проект? <a name = "what_project?"></a>
Реализовать структуры данных из стандартной библиотеки C++98 STL (vector, map, stack, set). Ниже я постараюсь объяснить, как это все реализовано.

## SFINAE <a name = "SFINAE"></a>
***SFINAE (substitution failure is not an error, неудавшаяся подстановка - не ошибка)*** - правило языка C++, связанное с шаблонами и перегрузкой функций.

***Правило SFINAE:***

Если не получается рассчитать окончательные типы/значения шаблонных параметров функции, компилятор не выбрасывает ошибку, а ищет другую подходящую перегрузку.

***Метапрограммирование*** - вид програмиироания, связанный с созданием программ, которые порождают другие программы как результат своей работы, либо программ, которые меняют себя во время выполнения.

В механизме SFINAE управление функциями происходит при помощи шаблонов.

Ошибки будут в следующих случаях:
* Не нашлось ни одной подходящей перегрузки.
* Нашлось несколько таких перегрузок, и компилятор не может решить, какую взять.
* Перегрузка нашлась, она оказалась шаблонной, и при инстанцировании шаблона случилась ошибка.

____

## Категории выражений(value categories) <a name = "value_categories"></a>

Каждое выражение в C++ характеризуется двумя независимыми свойствами: типом и категорией значения. Каждое выражение принадлежит к одному из трех основных категорий значений: prvalue, xvalue и lvalue.

Категории выражени lvalue и rvalue появились ещё в C. Исторически lvalue - это то, что может стоять слева от оператора присваивания, а rvalue - то, что может стоять только справа.

lvaule = rvalue;

В C++ эта терминология эволюционировала, в основу новой концепции легли еще 2 свойства:

* ***Наличие индетичности*** - наличие какого-то параметра, по которому можно понять, ссылаются ли два выражения на одну и ту же сущность или нет. Например, адрес в памяти.
* ***Возможность перемещения*** - поддерживает семантику перемещения, появилась со стандартом C++11.

***Иерархия категорий выражений***

![alt text](https://habrastorage.org/r/w1560/webt/2r/ut/w5/2rutw544jnidqrhi4cgwnc848xg.png)

***glvalue(generalized lvalue)*** - это выражение, оценка которого определяет идентичность объекта или функции

***prvalue(pure rvalue)*** - это выражение, оценка которого:
  1) вычисляет значение операнда встроенного оператора(такое prvalue не имеет объекта результата)
  2) инициализирует объект (считается, что такое prvalue имеет объект результата)

***xvalue(eXpiring)*** - это значение glvalue, которое обозначает объект, ресурсы которого можно использовать повторно.

______

## Итераторы  <a name = "Iterators"></a>
***Итератор*** - интерфейс, предоставляющий доступ к элементам коллекции (массива или контейнера) и навигацию по ним.

_____

### Названные требования(named requirements): LegacyIterator<a name = "LegacyIterator"></a>

Требования LegacyIterator описывают типы, которые могут использоваться для индентификации и обхода элементов контейнера.
LegacyIterator - это базовый набор требований, используемых другими типами итераторов: LegacyInputIterator, LegacyOutputIterator, LegacyBiderectionalIterator, LegacyRnadomIterator.

***Требования:***

Тип It удовлетворяет LegacyIterator если:
* [CopyConstructible](#CopyConstructible)
* [CopyAssignable](#CopyAssignable)
* [lvalues](#value_categories) типа It удовлетворяет [Swappable](#Swappable)
* [iterator_traits<It>](#iterator_traits) имеет определение членов value_type, difference_type, reference, pointer, iterator_category
* При заданном [rvalue](#value_categories) типа It следуюцие выражения должны быть действительными и иметь следующие свойства:
  
  *iterator - разыменование итератора, возвращаемый тип неопределен
  
  ++iterator - инкрементация итератора, возвращаемый тип it&
  
Итераторы не разыменовываются если:
  
  1) Они являются итераторами после конца или итераторами перед началом. На самом деле такие итераторы могут быть разыменованы, но требование предполагает, что это не так
  
  2) Они являются сингулярными итераторами, т.е. итераторами, не связанные с какой-либо последовательностью. Нулевой указатель, а также указатель, созданный по усполчанию, содержащий неопределенное значение, являтются сингулярными.
  
  3) Они были аннулированы одной из операций по аннулированию итератора в последовательности, на которую они ссылаются.
  
  ______

***CopyConstructible<a name = "CopyConstructible"></a>***
  
CopyConstructible указывает, что экземпляр типа может быть создан копированием из выражения [lvalue](#value_categories).

***Требования:***
  
  1) T u = v - значение u эквиваллентно v, значение v не меняется
  
  2) T(v) - значение T(v) эквиваллентно v, значение v не меняется
  
v - [lvalue](#value_categories) значение типа T или const T или [rvalue](#value_categories) значение типа const T,

u - произвольный идентификатор.
  
  _____
  
***CopyAssignable<a name = "CopyAssignable"></a>***

CopyAssignable указывает, что экземпляр типа может быть назначен копией из выражения [lvalue](#value_categories).

***Требования:***
  
  1) Тип T удовлетворяет MoveAssignable (с C++11)
  
  2) t = v - значение t эквивалентно значению v, значение v не изменилось. Тип возварата T&.
 
t - изменяемое выражение [lvalue](#value_categories) типа T,

v - [lvalue](#value_categories) выражение типа T или const T или [rvalue](#value_categories) выражение типа const T.
  
  ______
 
 ***Swappable<a name = "Swappable"></a>***
 
 Любое [lvalue](#value_categories) или [rvalue](#value_categories) этого типа может быть заменено любым [lvalue](#value_categories) или [rvalue](#value_categories) какого-либо другого типа, используя неквалифицированный вызов функции. 
 
 _____
  
### Иерархия и виды итераторов<a name = "hierarchy_and_types_iterators"></a>
 
***Иерархия итераторов:***
1) InputIterator <- ForwardIterator <- BidirectionalIterator <- RandomAccessIterator   
***InputIterator*** - гарантирует только одного прохождения для контейнеров. Выражения: i == j, i != j, *i, i->n, ++i, i++.
***ForwardIterator*** - гарантирует многопроходность для контейнеров. Выражения: те же выражения, что у InputIterator.
***BidirectionalIteraator*** - гарантирует перемещение в обоих направлениях. Выражения: те же выражения, что у ForwardIterator и  --i, i--.\
***RandomAccesIterator*** - гарантирует доступ к любому элементу контейнера за O(1). Выражения: те же выражения, что у BidirectionalIterator и i += n, i + n, 
i -=n, i - j, i[k], i < j, i > j, i >= j, i <= j.

где:

  i, j - итераторы,

  n, k - целые числа.
 
2) ***OutputIterator*** - считаются подной противоположностью итератором ввода, поскольку они выполняют функцию, противоположную иетратором ввода. Им могут быть присвоены значения последовательности, но они не могут использоваться для доступа к значениям, в отличие от иетраторов ввода. 

***Виды итераторов:***

***Константный итератор*** - итератор с помощью которого можно пройтись по контейнеру, но нельзя изменить значение разыменованного итератора.

***Обратный итератор (reverse iterator)*** - адаптер итератора, который меняет направление итератора.

В итоге есть три базовых типов итераторов: обычный, константный и обратный. Последние два можно объеденить между собой, тогда добавляется константный обратный итератор.
                                                
_____

### Шаблон iterator<a name = "template_iterator"></a>

***std::iterator*** - это базовый класс, предоставляемый для упрощения определений требуемых типов для итераторов.
Он не является классом итератора и не предоставляет никакой функциональности, которая должна быть у итератора.

***Определение класса:***

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> struct iterator;

***Шаблонные параметры:***

***Category*** - категория итератора. Должен быть одним из тегов приведенных выше.

***T*** - тип значений, которые могут быть получены путем разыменования итератора. Этот тип должен быть voidдля итераторов вывода.

***Distance*** - тип, который можно использовать для определения расстояния между итераторами.

***Pointer*** - определяет указатель на тип, повторяемый по (T).

***Reference*** - определяет ссылку на тип, повторяемый по (T).

***Реализация:***

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
______
### Iterator_traits<a name = "iterator_traits"></a>
 
***iterator_traits*** - это класс свойств типа, который предоставляет унифицированный интерфейс для свойств типов [LegacyIterator](#LegacyIterator).
 
***Определение iterator_traits:***

    template<class Iter>
    struct iterator_traits;

    template<class T>
    struct iterator_traits<T*>;

***Описание структуры iterator_traits***
 
***Параметры шаблона:***
 
***Iter*** - тип итератора для получения свойств типов полей структуры iterator_traits.
 
***T*** - тип предоставляемый пользователем, который может использоваться в качестве итератора.

***Типы полей структуры:***
 
***differrence_type*** - целочисленный тип, представляющий значения смещений итераторов относительно друг друга. Определение: Iter::differnce_type для шаблона с типом Iter, std::ptrdiff_t для шаблона с типом T.
 
***value_type*** - тип значения, на которое указывает итератор. Определение: Iter::value_type для шаблона с типом Iter, T для шаблона с типом T.
 
***pointer*** - тип указателя, возвращаемого при обращении к объекту итератора через operator->. Определение: Iter::pointer для шаблона с типом Iter, T* для шаблона с типом T.
 
***reference*** - тип ссылки, возвращаемой при разыменовании итератора. Определение: Iter::reference для шаблона с типом Iter, T& для шаблона с типом T.
 
***iterator_category*** - тип, указывающий на набор операций, поддерживаемых итератором. Определение: Iter::iterator_category для шаблона с типом Iter.
Определение: std :: random_access_iterator_tag для шаблона с типом T.

***Категории итераторов:***
 
* random_access_iterator_tag. random_access_iterator_tag — наследник bidirectional_iterator_tag.

* bidirectional_iterator_tag. bidirectional_iterator_tag является наследником forward_iterator_tag.
 
* forward_iterator_tag. forward_iterator_tag является наследником input_iterator_tag и output_iterator_tag.
 
* input_iterator_tag.
 
* output_iterator_tag.

***Реализация iterator_traits***
 
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
__________
## Обратный итератор<a name = "reverse_iterator"></a>

***reverse_iterator*** - это адаптер итератора, который меняет направление данного итератора, который должен быть как минимум BidirectionalIterator.

Другими словами, при наличии двунаправленного итератора std::reverse_iterator создает новый итератор, который перемещается от конца к началу последовательности, определенной базовым двунаправленным итератором.
_______
			
Определение:<a name= "reverse_def"></a>
			
    template< class Iter >
    class reverse_iterator;

_______
			
Типы параметров:<a name = "reverse_types"></a>

|Тип параметра	  |Определение					|
|-----------------|---------------------------------------------|
|iterator_type	  |Iter	     					|
|iterator_category|std::iterator_traits<Iter>::iterator_category|
|value_type	  |std::iterator_traits<Iter>::value_type       |
|difference_type  |std::iterator_traits<Iter>::difference_type  |
|pointer	  |std::iterator_traits<Iter>::pointer 		|
|reference	  |std::iterator_traits<Iter>::reference	|

__________
	
### Поля:<a name = "reverse_fields"></a>

current - базовый итератор(protected).
________
			
### Методы:<a name = "reverse_methods"></a>
			
Ниже представленные функции класса объявлены в public секции.
			
***Constructor***<a name = "reverse_constructor"></a>

Создает новый адаптер для итератора

1) reverse_iterator();
		
Конструктор по умолчанию. Базовый итератор инициализируется значением.
			
Реализация:
			
    reverse_iterator(): current() {};
			
2) explicit reverse_iterator(iterator_type x);
	
Базовый итератор инициализируется с помощью x.

explicit указывает, что конструктор является явным, то есть его нельзя использовать для неявных преобразований и инициализации копирования.

Например:

A a1 = 1 - ошибка
			
A a1 = a2 - ошибка
			
A a1(1) - OK
			
A a1 = (A)1 - OK, явное приведение.
			
Реализация:
			
    explicit reverse_iterator(iterator_type x): current(x) {};			

3) 
    template<class U>			
    reverse_iterator(const reverse_iterator<U>& other);
			
Базовый итератор инициализируется итератором other.
			
Реализация:
			
    template<class U>
    reverse_iterator(const reverse_iterator<U>& other):current(other.base()) {};

______

***operator =***<a name = "reverse_="></a>
			
Базовым итератор присваивается значение базового итератора other, то есть other.base(). Возвращает *this.
			
    template< class U >			
    reverse_iterator& operator=( const reverse_iterator<U>& other );
			
Реализация:

    template<class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        this->current = static_cast<reverse_iterator<Iterator> >(other.base());
        return *this;
    };

______
			
***base***<a name = "reverse_base"></a>

Возвращает базовый итератор.
		
    iterator_type base() const;
			
Реализация:

    iterator_type base() const
    {
        return this->current;
    };

_____
			
***operator \****<a name = "reverse_star"></a>
			
    reference operator*() const;
			
Эквивалентно Iter tmp = current; return *--tmp;. Возвращает ссылку на элемент предшествующий current.
			
Реализация:
	
    reference operator*() const
    {
        Iterator tmp = this->current;
        return *--tmp;
    };
			
______
			
***operator ->***<a name = "reverse_arrow"></a>
			
    pointer operator->() const;
			
Внутри функция вызывает operator * и возвращает свой адрес.
			
Реализация:
			
    pointer operator->() const
    {
        return &(operator*());
    };
			
______

***operator []***<a name = "reverse_[]"></a>
			
    reference operator[] (difference_type n) const;
			
Доступ к элементу, расположенному в n позициях от элемента, на который в данный момент указывает итератор. Если такой элемент не существует, это вызывает неопределенное поведение.
			
Реализация:

    reference operator[] (difference_type n) const
    {
        return *(*this + n);
    };
			
______

***operator ++***<a name = "reverse_++"></a>
			
    reverse_iterator& operator++();
			
Преинкремент итератора.
			
Реализация:
			
    reverse_iterator& operator++()
    {
        --(this->current);
        return *this;
    };
			
_______

***operator --***<a name = "reverse_--"></a>
			
    reverse_iterator& operator--();

Предекремент итератора.
			
Реализация:
			
    reverse_iterator& operator--()
    {
        ++(this->current);
        return *this;
    };
			
______
			
***operator ++(int)***<a name = "reverse_++_int"></a>
			
    reverse_iterator operator++(int);

Постинкремент итератора.
			
Реализация:
			
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp(*this);

        --(this->current);
        return tmp;
    };
			
_______

***operator --(int)***<a name = "reverse_--_int"></a>
			
    reverse_iterator operator--(int);

Постинкремент итератора.
			
Реализация:
			
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp(*this);

        ++(this->current);
        return tmp;
    };
			
_______
			
***operator +***<a name = "reverse_+"></a>
			
    reverse_iterator operator+(difference_type n) const;
			
Возвращает итератор, который сдвинут на n позиций.
			
Реализация:
			
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(this->current - n);
    };

_______
			
***operator -***<a name = "reverse_-"></a>
			
    reverse_iterator operator-(difference_type n) const;
			
Возвращает итератор, который сдвинут на -n позиций.
			
Реализация:
			
    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(this->current + n);
    };

_______

***operator +=***<a name = "reverse_+="></a>
			
    reverse_iterator& operator+=(difference_type n);
			
Перемещает итератор на позицию +n.
			
Реализация:
			
    reverse_iterator operator+=(difference_type n) const
    {
        this->current -= n;
        return *this;
    };
			
________
			
***operator -=***<a name = "reverse_-="></a>
			
    reverse_iterator& operator-=(difference_type n);
			
Перемещает итератор на позицию -n.
			
Реализация:
			
    reverse_iterator operator-=(difference_type n) const
    {
        this->current += n;
        return *this;
    };			

______
			
### Функции, не являющиеся членами класса<a name = "reverse_non_member"></a>			
			
***operator ==***<a name = "reverse_=="></a>

    template< class Iterator1, class Iterator2 >
    bool operator==(const ft::reverse_iterator<Iterator1>& lhs, 
        const ft::reverse_iterator<Iterator2>& rhs);
			
Реализация:
    
    template<class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }
			
______
			
***operator !=***<a name = "reverse_!="></a>
			
    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
        const ft::reverse_iterator<Iterator2>& rhs);
			
Реализация:
    
    template<class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() != rhs.base();
    }
			
______
			
***operator <, <=, >, >=***<a name = "reverse_cmp"></a>
			
    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
        const ft::reverse_iterator<Iterator2>& rhs);
			
    template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
        const ft::reverse_iterator<Iterator2>& rhs);
			
    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
        const ft::reverse_iterator<Iterator2>& rhs);
			
    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
        const ft::reverse_iterator<Iterator2>& rhs);
			
Реализации:
			
    template<class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }
			
    template<class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() <= rhs.base();
    }
			
    template<class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }
			
    template<class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() >= rhs.base();
    }
_______
			
***operator+(reverse_iterator)***<a name = "reverse_plus"></a>
			
    template<class Iter>
    reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,
        const reverse_iterator<Iter>& it);
			
Возвращает инкрементированный итератор на n.
			
Реализация:
			
    template<class Iter>
    reverse_iterator<Iter>
    operator+(typename reverse_iterator<Iter>::difference_type n,
        const reverse_iterator<Iter>& it)
    {
        return reverse_iterator<Iter>(it.base() - n);
    }
			
______
			
***operator-(reverse_iterator)***<a name = "reverse_minus"></a>
			
    template<class Iterator>
    typename reverse_iterator<Iterator>::difference_type
        operator-( const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs );
			
Возвращает расстояние между двумя адапторами итераторов.
			
Реализация:
			
    template<class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }
			
_____

## enable_if<a name = "enable_if"></a>
			
    template<bool B, class T = void>
    struct enable_if;
			
Если B true, enable_if имеет публичный член typedef type, равный T, в противном случае член typedef отсутствует. Эта метафункция - это удобный способ использования [SFINAE](#SFINAE) для выбора правильной перегруженной фукнции, если B false, то компилятор условно удаляеет перегруженную функцию, т.к. у нее нет типа. enable_if можно использовать как дополнительный аргумент функции (не применимо к перегрузкам операторов), как тип возвращаемого значения (не применимо к конструкторам и деструкторам) или как шаблон класса или параметр шаблона функции.
			
Реализация:
			
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
			
_____
			
## integral_constant<a name = "integral_constant"></a>
			
    template<class T, T v>
    struct integral_constant;
			
Обертка над статическими константами указанного типа. Это иногда полезно, особенно в метапрограммировании, ведь идет программирование типов, а не значений.
			
Реализация:
			
    template<class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator value_type() const {return value;}
    };			
			
***value*** - статическая константа типа T со значением v,
			
***operator value_type() const*** - функция преобразования, возвращает значение в оболочке.
			
Для T равного bool существуют два typedef:
			
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
			
			
_________
			
## is_integral<a name = "is_integral"></a>
			
    template< class T >
    struct is_integral;
			
Класс признаков, который определяет, является ли T целочисленным типом. Он наследует от integral_constant либо как true_type или false_type, в зависимости от того, Т представляет собой интегральный тип:			
			
|фундаментальные итегральные типы|
|--------------------------------|
|bool				 |
|char				 |
|signed char			 |
|unsigned char			 |
|wchar_t			 |
|char16_t			 |
|char32_t			 |
|short				 |
|unsigned short			 |
|int				 |
|unsigned int			 |
|long				 |
|unsigned long			 |
|long long			 |
|unsigned long long		 |

Реализация:
			
    template<class T> struct is_integral: public false_type {};
    template<> struct is_integral<bool>: public true_type {};
    template<> struct is_integral<char>: public true_type {};
    template<> struct is_integral<signed char>: public true_type {};
    template<> struct is_integral<unsigned char>: public true_type {};
    template<> struct is_integral<wchar_t>: public true_type {};
    template<> struct is_integral<char16_t>: public true_type {};
    template<> struct is_integral<char32_t>: public true_type {};
    template<> struct is_integral<short>: public true_type {};
    template<> struct is_integral<unsigned short>: public true_type {};
    template<> struct is_integral<int>: public true_type {};
    template<> struct is_integral<unsigned int>: public true_type {};
    template<> struct is_integral<long>: public true_type {};
    template<> struct is_integral<unsigned long>: public true_type {};
    template<> struct is_integral<long long>: public true_type {};
    template<> struct is_integral<unsigned long long>: public true_type {};

________

## lexicographical_compare<a name = "lexicographical_compare"></a>

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
        InputIt2 first2, InputIt2 last2);

    template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	    InputIt2 first2, InputIt2 last2, Compare comp);

Возвращает, true если лексикографически диапазон [first1,last1) сравнивается меньше, чем диапазон [first2,last2).
Лексикографическое сравнение обычно используется для сортировки слов по алфавиту в словарях.
Оно включает в себя последовательное сравнение элементов, имеющих одинаковую позицию в обоих диапазонах, друг с другом до
тех пор, пока один элемент не станет эквивалентным другому. Результат сравнения этих первых несовпадающих элементов 
является результатом лексикографического сравнения. Если обе последовательности сравниваются до тех пор, пока одна
из них не закончится, более короткая последовательность лексикографически меньше, чем более длинная. В первой версии для
сравнения используется operator <, а во второй функцию компаратор.
Реализация:

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
        InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	    InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return false;
	}

_______

## equal<a name = "equal"></a>

    template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);

    template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p);

Сравнивает элементы в диапазоне [first1,last1) с элементами в диапазоне, начинающемся с first2, и возвращает, true 
если все элементы в обоих диапазонах совпадают. Элементы сравниваются с помощью operator== или с помощью предиката.

Реализация:

    template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}

    template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			   BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}

______

## pair<a name = "pair"></a>

    template<class T1, class T2>
    struct pair;

Этот класс объединяет пару значений, которые могут быть разных типов (Т1, а также Т2). Доступ к отдельным значениям можно
получить через его публичные члены: first, second.

Параметры шаблона:

|Тип участника|Определение|
|-------------|-----------|
|T1           |first_type  |
|T2           |second_type|

Поля:

|Имя поля|Тип|
|--------|---|
|first    |T1 |
|second  |T2 |

Методы:

1. Конструкторы:

Конструктор по умолчанию.

        pair() {};
   
Конструктор инициализации.
    
        pair(const T1& x, const T2& y) {};

Конструктор копирования.
    
        template<class U1, class U2>
        pair(const pair<U1, U2>& p) {};

Реализация:

    pair(): first(), second() {}
    pair(const T1& x, const T2& y): first(x), second(y) {}
    template<class U1, class U2>
    pair(const pair<U1, U2>& p): first(p.first), second(p.second) {}

2. operator=

       pair& operator=(const pair& other){};

Копирование контента other в текущий объект.

Реализация:

    pair& operator=(const pair& other)
    {
        this->first = other.first;
        this->second = other.second;
        return *this;
    }

3. Реализация функций, не являющихся членами:
    
        template<class T1, class T2>
        bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
            return  lhs.first == rhs.first && lhs.second == rhs.second;
        }
   
        template<class T1, class T2>
        bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
        return !(lhs == rhs);
        }

        template<class T1, class T2>
        bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
            return (lhs.first < rhs.first || (!(rhs.first < lhs.first)
                && lhs.second < rhs.second));
        }

        template<class T1, class T2>
        bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
            return !(rhs < lhs);
        }

        template<class T1, class T2>
        bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
            return rhs < lhs;
        }

        template<class T1, class T2>
        bool operator>=(const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs)
        {
            return !(lhs < rhs);
        }

______

## make_pair<a name = "make_pair"></a>

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y);

Создает pair объект с его первым элементом x, а его вторым элементом y.

Реализация:

    template<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}

______

## allcoator<a name = "allcoator"></a>

***allcoator*** - это класс, который определяет модель памяти, по сути это рапределитель памяти, который позволяет управлять
памятью. В данном проекте разрешено испоьзовать стандартный аллокатор. Но хорошо было бы узнать как он работает, ведь 
контейнеры используют его.

Объявление аллокатора в заголовочном файле:

    template <class T> class allocator;

***T*** - тип элементов, выделенных объектов.

### Типы определенные в аллокаторе<a name="allocator_types"></a>

|Тип       |Определение в аллокаторе|Описание            |
|----------|------------------------|------------------------------------------------------------------------------------------|
|value_type|T                       |Тип элемента                                                                              |
|pointer   |T*                      |Указатель на элемент                                                                      |
|reference |T&|Ссылка на элемент                                                                                               |
|const_pointer|const T*|Указатель на константный элемент                                                                       |
|const_reference|const T&|Ссылка на константный элемент                                                                        |
|size_type|size_t|Количесвто элементов                                                                                         |
|difference_type|ptrdiff_t                                                        |Разница между двумя указатеями              |
|rebind_type|template <class Type> struct rebind {typedef allocator<Type> other;};|Тип other это тип аллокатора c типом Type| 

### Конструкторы аллокатора<a name = "allocator_constructors"></a>

    //default constructor
    allocator() throw();

    //copy constructor
    allocator (const allocator& alloc) throw();
    template <class U>
    allocator (const allocator<U>& alloc) throw();

Создает объект аллокатора.
Стандартный аллокатор не имеет членов данных и не обязан выполнять инициализацию, но три версии конструктора должны быть 
определены (даже если они ничего не делают), чтобы обеспечить возможность копирования конструкций из объектов 
аллокаторов других типов.

***alloc*** - объект аллокатора

### Деструктор<a name="allocator_destructor"></a>

    ~allocator ( ) throw;

Уничтожает объект аллокатора

### address<a name = "allocator_address"></a>

     pointer address ( reference x ) const;
     const_pointer address ( const_reference x ) const;

Возвращает адрес x.
В стандартном распределителе по умолчанию это фактически означает возврат &x.

***x*** - Ссылка на объект.
reference и const_reference являются типами-членами (определены как псевдонимы T& и const T& соответственно в std::allocator<T>).

### allocate<a name = "allocate"></a>

    pointer allocate (size_type n, allocator<void>::const_pointer hint=0);

Выделяет блок хранения.
Пытается выделить блок памяти с размером, достаточным для содержания n элементов типа value_type (псевдоним параметра шаблона аллокатора), и возвращает указатель на первый элемент.
Хранилище выравнивается соответствующим образом для объектов типа value_type, но они не строятся.
В стандартном распределителе по умолчанию блок памяти выделяется с помощью ::operator new один или несколько раз и выбрасывает ошибку bad_alloc, если не может выделить весь запрошенный объем памяти.

***n*** - Количество элементов (каждый размером sizeof(value_type)), которые будут выделены.
Тип-член size_type является псевдонимом size_t (в стандартном распределителе по умолчанию) size_t является беззнаковым интегральным типом.

***hint*** - Либо 0, либо значение, ранее полученное другим вызовом allocate и еще не освобожденное с помощью deallocate.
Если значение не равно 0, оно может быть использовано как подсказка для повышения производительности путем выделения 
нового блока рядом с указанным. Адрес соседнего элемента часто является хорошим выбором.

### deallocate<a name = "deallocate"></a>

    void deallocate (pointer p, size_type n);

Освобождает блок хранения.
Освобождает блок хранения, ранее выделенный с помощью члена allocate и еще не освобожденный.
Элементы массива не уничтожаются при вызове этой функции-члена.
В распределителе по умолчанию блок хранения в какой-то момент деаллоцируется с помощью ::operator delete (либо во время вызова функции, либо позже).

### max_size<a name= "allocator_max_size"></a>

    size_type max_size() const throw();

Максимально возможный размер для выделения
Возвращает максимальное количество элементов, каждый из которых имеет тип члена value_type (псевдоним параметра шаблона allocator), которые потенциально могут быть выделены вызовом member allocate.
Вызов allocate со значением, возвращаемым этой функцией, может не выделить запрашиваемое хранилище.

### construct<a name = "construct"></a>

    void construct (pointer p, const_reference val);

Вызывает явно конструктор со значением val у объекта с указателем p.

***p*** - указатель объекта у которого вызывается конструктор

***val*** - значение с которым будет инициализироваться объект

### destroy<a name = destroy></a>

    void destroy (pointer p);

Вызывает явно деструктор у объекта, указатель которого p.

***p*** - указатель объекта у которого вызывается деструктор
______
## Vector<a name = "Vector"></a>

***Vector*** - Векторы - это контейнеры последовательностей, представляющие массивы, размер которых может изменяться.
Как и массивы, векторы используют непрерывные места хранения для своих элементов, что означает, что к их элементам также
можно получить доступ, используя смещения в обычных указателях на его элементы, причем так же эффективно, как и в 
массивах. Но в отличие от массивов их размер может изменяться динамически, а их хранение автоматически обрабатывается 
контейнером. Внутри векторы используют динамически распределенный массив для хранения своих элементов. Возможно, 
потребуется перераспределить этот массив, чтобы он увеличивался в размере при вставке новых элементов, что подразумевает
выделение нового массива и перемещение в него всех элементов. Это относительно дорогостоящая задача с точки зрения 
времени обработки, и поэтому векторы не перераспределяются каждый раз, когда элемент добавляется в контейнер.
Вместо этого векторные контейнеры могут выделять некоторую дополнительную память, чтобы приспособиться к возможному 
росту, и, таким образом, контейнер может иметь фактическую емкость больше, чем хранилище, строго необходимое для 
хранения его элементов. Следовательно, по сравнению с массивами, векторы потребляют больше памяти в обмен на возможность
управлять хранилищем и эффективно динамически расти.
