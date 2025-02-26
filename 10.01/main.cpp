#include <list>
#include <ctime>

/*
ОБЩАЯ ИДЕЯ:
Будем хранить шахматную партию в нодах односвязного списка в специальных структурах.

ОПИСАНИЕ СТРУКТУРЫ:
(см комментарии в структуре)
Поля в структуре расположены так, чтобы структура имелла минимальный padding

АРГУМЕНТАЦИЯ ИСПОЛЬЗОВАНИЯ СПИСКА:
1. Нужна динамически-расширяемая структура, так как партии могут быть разной длинны
2. Список не требует целостности по памяти, то есть вставка всегда будет производиться за O(1) в отличие от вектора (вектор может произвести реаллокацию)
3. Поскольку список хранит дополнительную информацию (указатель или 2 указателя в случае двусвязного списка) полезная нагрузка в ноде
должна превышать по размеру размер 2х указателей, чтобы оправдать использование структуры. Даже без хранения времени в ноде это условие выполнено.
4. Вставки новых ходов всегда происходят только в конец
5. При использовании списка в конце партии не остается неиспользованного места (которое может остаться в векторе за счет аллокаций)
*/

struct Step {
    std::tm ltm; // момент времени, когда был сделан ход (optional -- можно убрать)
    char chess_color; // за кого сделан ход (белые или черные). Не используется bool, на него все равно целый байт выделяется
    /*
    Описание хода текстом в западной нотации. Всего любой ход можно описать не более чем 7 символами:
    1 символ -- название фигуры
    2 символа -- начальное поле фигуры
    1 символ -- ход (обычный ход или взятие вражеской фигуры)
    2 символа -- конечное поле
    1 символ -- дополнительный (если ходом дали шах или мат)

    Ракировки обозначаются O-O и O-O-O и укладываются в 7 символов
    */
    char step[7];
};

int main() {

}