# ft_containers Методичка

## Содержание:
* [О чем проект?](#what_project?)
* [Немного о SFINAE](#SFINAE)
* [Категории выражений](#value_categories)
* [Итераторы](#Iterators)
  * [Названные требования(named requirements): LegacyIterator](#LegacyIterator)
  * [Иерархия и виды итераторов](#hierarchy_and_types_iterators)
  * [Iterator traits](#iterator_traits)
  * [Описание структуры iterator_traits](#struct_iterator_traits)
  * [Реализация iterator_traits](#realization_iterator_traits)
  * [Класс iterator](#class_iterator)

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

## Названные требования(named requirements): LegacyIterator<a name = "LegacyIterator"></a>

Требования LegacyIterator описывают типы, которые могут использоваться для индентификации и обхода элементов контейнера.
LegacyIterator - это базовый набор требований, используемых другими типами итераторов: LegacyInputIterator, LegacyOutputIterator, LegacyBiderectionalIterator, LegacyRnadomIterator.

***Требования:***

Тип It удовлетворяет LegacyIterator если:
* [CopyConstructible](#CopyConstructible)
* [CopyAssignable](#CopyAssignable)
* [lvalues](#value_categories) типа It удовлетворяет [Swappable](#Swappable)
* [iterator_traits<It>](#iterator_traits) имеет определение членов value_type, difference_type, reference, pointer, iterator_category
* При заданном rvalue типа It следуюцие выражения должны быть действительными и иметь следующие свойства:
  
  *iterator - разыменование итератора, возвращаемый тип неопределен
  
  ++iterator - инкрементация итератора, возвращаемый тип it&
  
Итераторы не разыменовываются если:
  
  1) Они являются итераторами после конца или итераторами перед началом. На самом деле такие итераторы могут быть разыменованы, но требование предполагает, что это не так
  
  2) Они являются сингулярными итераторами, т.е. итераторами, не связанные с какой-либо последовательностью. Нулевой указатель, а также указатель, созданный по усполчанию, содержащий неопределенное значение, являтются сингулярными.
  
  3) Они были аннулированы одной из операций по аннулированию итератора в последовательности, на которую они ссылаются.
  
  ______

***CopyConstructible<a name = "CopyConstructible"></a>***
  
CopyConstructible указывает, что экземпляр типа может быть создан копированием из выражения lvalue.

***Требования:***
  
  1) T u = v - значение u эквиваллентно v, значение v не меняется
  
  2) T(v) - значение T(v) эквиваллентно v, значение v не меняется
  
v - lvalue значение типа T или const T или rvalue значение типа const T,

u - произвольный идентификатор.
  
  _____
  
***CopyAssignable<a name = "CopyAssignable"></a>***

CopyAssignable указывает, что экземпляр типа может быть назначен копией из выражения lvalue.

***Требования:***
  
  1) Тип T удовлетворяет MoveAssignable (с C++11)
  
  2) t = v - значение t эквивалентно значению v, значение v не изменилось. Тип возварата T&.
 
t - изменяемое выражение lvalue типа T,

v - lvalue выражение типа T или const T или rvalue выражение типа const T.
  
  ______
 
 ***Swappable<a name = "Swappable"></a>***
 
 Любое lvalue или rvalue этого типа может быть заменено любым lvalue или rvalue какого-либо другого типа, используя неквалифицированный вызов функции. 
 
 _____
  
## Иерархия и виды итераторов<a name = "hierarchy_and_types_iterators"></a>
 
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

## Iterator_traits<a name = "iterator_traits"></a>
 
***iterator_traits*** - это класс свойств типа, который предоставляет унифицированный интерфейс для свойств типов [LegacyIterator](#LegacyIterator).
 
Определение итератора:
 
1) template< class Iter >
   
   struct iterator_traits;
 
2) template< class T >
 
   struct iterator_traits< T* >;
 
## Описание структуры iterator_traits<a name = "struct_iterator_traits"></a>
 
Параметры шаблона: 
 
***Iter*** - тип итератора для получения свойств типов полей структуры iterator_traits.
 
***T*** - тип предоставляемый пользователем, который может использоваться в качестве итератора.

Типы полей структуры:
 
***differrence_type*** - целочисленный тип, представляющий значения смещений итераторов относительно друг друга. Определение: Iter::differnce_type для шаблона с типом Iter, std::ptrdiff_t для шаблона с типом T.
 
***value_type*** - тип значения, на которое указывает итератор. Определение: Iter::value_type для шаблона с типом Iter, T для шаблона с типом T.
 
***pointer*** - тип указателя, возвращаемого при обращении к объекту итератора через operator->. Определение: Iter::pointer для шаблона с типом Iter, T* для шаблона с типом T.
 
***reference*** - тип ссылки, возвращаемой при разыменовании итератора. Определение: Iter::reference для шаблона с типом Iter, T& для шаблона с типом T.
 
***iterator_category*** - тип, указывающий на набор операций, поддерживаемых итератором. Определение: Iter::iterator_category для шаблона с типом Iter.
Определение: std :: random_access_iterator_tag для шаблона с типом T.

Категории итераторов:
 
* random_access_iterator_tag. random_access_iterator_tag — наследник bidirectional_iterator_tag.

* bidirectional_iterator_tag. bidirectional_iterator_tag является наследником forward_iterator_tag.
 
* forward_iterator_tag. forward_iterator_tag является наследником input_iterator_tag и output_iterator_tag.
 
* input_iterator_tag.
 
* output_iterator_tag.

## Реализация iterator_traits<a name = "realization_iterator_traits"></a>
 
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

## Класс iterator<a name = "class_iterator"></a>
	
Определение класса:

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> struct iterator;
			
Шаблонные параметры:

***Category*** - категория итератора. Должен быть одним из тегов приведенных выше.

***T*** - тип значений, которые могут быть получены путем разыменования итератора. Этот тип должен быть voidдля итераторов вывода.

***Distance*** - тип, который можно использовать для определения расстояния между итераторами.
			
***Pointer*** - определяет указатель на тип, повторяемый по (T).
			
***Reference*** - определяет ссылку на тип, повторяемый по (T).			
