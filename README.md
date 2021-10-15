# ft_containers

## Содержание:
* [О чем проект?](#what_project?)
* [Немного о SFINAE](#SFINAE)

## О чем проект? <a name = "what_project?"></a>
Реализовать структуры данных из стандартной библиотеки C++ STL (vector, map, stack, set). Ниже я постараюсь объяснить, как это все реализовано (по сути мини-методичка).

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
