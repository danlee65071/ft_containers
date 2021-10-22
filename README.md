# ft_containers Методичка

## Содержание:
* [О чем проект?](#what_project?)
* [Немного о SFINAE](#SFINAE)
* [Категории выражений](#value_categories)
* [Итераторы](#Iterators)

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

***xvalue(eXpiring)*** - это значение glvalue, которое обозначает объект, ресурсы которого можно использовать повторно

## Итераторы  <a name = "Iterators"></a>
***Итератор*** - интерфейс, предоставляющий доступ к элементам коллекции (массива или контейнера) и навигацию по ним.

***Названные требования(named requirements): LegacyIterator***

Требования LegacyIterator описывают типы, которые могут использоваться для индентификации и обхода элементов контейнера.
LegacyIterator - это базовый набор требований, используемых другими типами итераторов: LegacyInputIterator, LegacyOutputIterator, LegacyBiderectionalIterator, LegacyRnadomIterator.

***Требования:***

Тип It удовлетворяет LegacyIterator если:
* CopyConstructible
* CopyAssignable
* lvalues типа It удовлетворяет Swappable
* iterator_traits<It> имеет определение членов value_type, difference_type, reference, pointer, iterator_category
* При заданном rvalue типа It следуюцие выражения должны быть действительными и иметь следующие свойства:
  
  *iterator - разыменование итератора, возвращаемый тип неопределен
  
  ++iterator - инкрементация итератора, возвращаемый тип it&
  
Итераторы не разыменовываются если:
  
  1) Они являются итераторами после конца или итераторами перед началом. На самом деле такие итераторы могут быть разыменованы, но требование предполагает, что это не так
  
  2) Они являются сингулярными итераторами, т.е. итераторами, не связанные с какой-либо последовательностью. Нулевой указатель, а также указатель, созданный по усполчанию, содержащий неопределенное значение, являтются сингулярными.
  
  3) Они были аннулированы одной из операций по аннулированию итератора в последовательности, на которую они ссылаются

***CopyConstructible***
  
CopyConstructible указывает, что экземпляр типа может быть создан копированием из выражения lvalue.

***Требования:***
  
  1) T u = v - значение u эквиваллентно v, значение v не меняется
  
  2) T(v) - значение T(v) эквиваллентно v, значение v не меняется
  
v - lvalue значение типа T или const T или rvalue значение типа const T,

u - произвольный идентификатор.
  
***CopyAssignable***
  
  
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

***Iterator_traits***


