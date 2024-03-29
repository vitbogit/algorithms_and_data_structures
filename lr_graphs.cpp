﻿#include <iostream>
#include <fstream>

using namespace std;


// Глобальные переменные:
string gl_input_file_name = "input_1.txt"; // Имя файла входных данных



// Объявление функций:
// 1-ая группа функций:
void graph_read_from_console(int* number_of_vertices, int*** adjacency_matrix); // Чтение данных из консоли
void graph_read_from_file(int* number_of_vertices, int*** adjacency_matrix); // Чтение данных из файла
void graph_print(int* number_of_vertices, int*** adjacency_matrix); // Печать графа
// 2-ая группа функци:
void graph_dijkstra(int* number_of_vertices, int*** adjacency_matrix, int start_vertex, int end_vertex); // Поиск кратчайшего пути между двумя вершинами графа (Дейкстра)
void graph_make_undirected(int* number_of_vertices, int*** adjacency_matrix); // Функция лишения ребр графа ориентации (граф становится неориенинтированным)
void graph_build_spanning_tree(int* number_of_vertices, int*** adjacency_matrix); // Построение остовного дерева минимальной стоимости (Прима)

// Основная программа:
int main()
{


    // Подключение русского языка в консоли:
    setlocale(LC_ALL, "Russian");


    // Объявление переменных:
    int number_of_vertices; // Число вершин графа
    int** adjacency_matrix; // Матрица смежности
    string user_input; // Пользовательский ввод
    int start_vertex; // Начальная вершина для нахождения кратчайшего пути
    int end_vertex; // Конечная вершина для нахождения кратчайшего пути 


    // Выбор пользователем режима ввода данных - через консоль или файл
    cout << "Выберите режим ввода данных: консоль (1) или файл (2): ";
    cin >> user_input;


    // Проверка ответа пользователя на корректность:
    while (user_input != "1" && user_input != "2") {

        // Повторный выбор пользователем режима ввода данных - через консоль или файл
        cout << "Некорректный ввод. Выберите режим ввода данных: консоль (1) или файл (2): ";
        cin >> user_input;

    } // Конец блока "Проверка ответа пользователя на корректность"


    // Осуществляем ввод данных:
    if (user_input == "1") { // Осуществляем ввод данных из консоли


        // Вызов функции ввода из консоли:
        graph_read_from_console(&number_of_vertices, &adjacency_matrix);


    } // Конец блока "Осуществляем ввод данных из консоли"
    else { // Осуществляем ввод данных из файла


        // Вызов функции ввода из файла:
        graph_read_from_file(&number_of_vertices, &adjacency_matrix);


    } // Конец блока "Осуществляем ввод данных из файла"


    // Распечатаем считанный граф:
    graph_print(&number_of_vertices, &adjacency_matrix);


    // Ввод пользователем начальной и конечной вершины графа для нахождения между ними кратчайшего пути:
    cout << "\n\n\n\nВведите начальную и конечную вершину для нахождения кратчайшего пути: ";
    cin >> start_vertex >> end_vertex;
    cout << "\n\n\n";


    // Проверка на корректность ввода начальной и конечной вершины:
    while (start_vertex < 0 || end_vertex >= number_of_vertices) {
        
        // Повторный ввод пользователем начальной и конечной вершины графа для нахождения между ними кратчайшего пути:
        cout << "Некорректный ввод. Введите начальную и конечную для нахождения кратчайшего пути: ";
        cin >> start_vertex >> end_vertex;

    } // Конец блока "Проверка на корректность ввода начальной и конечной вершины"


    // Вызов функции алгоритма нахождения кратчайшего пути между вершинами (алгоритм Дейкстры):
    graph_dijkstra(&number_of_vertices, &adjacency_matrix, start_vertex, end_vertex);


    // Предупредим пользователя о том, что граф становится неориентированным:
    cout << "\n\n\n\nГраф становится неориентированным...\n\n\n\n";


    // Вызов функции, делающей граф неориентированным:
    graph_make_undirected(&number_of_vertices, &adjacency_matrix);


    // Распечатаем ставший неориентированным граф:
    graph_print(&number_of_vertices, &adjacency_matrix);


    // Построим остовное дерево (алгоритм Прима):
    graph_build_spanning_tree(&number_of_vertices, &adjacency_matrix);


} // Конец блока "Основная программа"



// Чтение данных из консоли:
void graph_read_from_console(int* number_of_vertices, int*** adjacency_matrix) {


    // -------------------------------------
    // ---------- 1: Число вершин ----------
    // -------------------------------------


    // Приглашение к вводу числа вершин графа:
    cout << "Введите число вершин графа: ";


    // Ввод числа вершин графа
    cin >> *number_of_vertices;


    // -------------------------------------
    // ------- 2: Матрица смежности --------
    // -------------------------------------


    // Выделим память под матрицу смежности:
    *adjacency_matrix = new int* [*number_of_vertices]; 


    // Приглашение к вводу матрицы смежности:
    cout << "Введите матрицу смежности графа: ";


    // Ввод матрицы смежности:
    for (int i = 0; i < *number_of_vertices; i++) {


        // Создадим i-ую строку:
        *(*adjacency_matrix + i) = new int[*number_of_vertices];


        // Заполним i-ую строку:
        for (int j = 0; j < *number_of_vertices; j++) {


            // Ввод очередного элемента матрицы смежности:
            cin >> *(*(*adjacency_matrix + i) + j);


        } // Конец блока "Заполним i-ую строку"


    } // Конец блока "Ввод матрицы смежности"


} // Конец блока "Чтение данных из консоли"



// Чтение данных из файла:
void graph_read_from_file(int* number_of_vertices, int*** adjacency_matrix) {


    fstream file; // Поток ввода данных из файла

    file.open(gl_input_file_name); // Открытие файла исходных данных


    // -------------------------------------
    // ---------- 1: Число вершин ----------
    // -------------------------------------


    // Ввод числа вершин графа
    file >> *number_of_vertices;



    // -------------------------------------
    // ------- 2: Матрица смежности --------
    // -------------------------------------


    // Выделим память под матрицу смежности:
    *adjacency_matrix = new int* [*number_of_vertices];


    // Ввод матрицы смежности:
    for (int i = 0; i < *number_of_vertices; i++) {


        // Создадим i-ую строку:
        *(*adjacency_matrix + i) = new int[*number_of_vertices];


        // Заполним i-ую строку:
        for (int j = 0; j < *number_of_vertices; j++) {


            // Ввод очередного элемента матрицы смежности:
            file >> *(*(*adjacency_matrix + i) + j);


        } // Конец блока "Заполним i-ую строку"


    } // Конец блока "Ввод матрицы смежности"


    file.close(); // Закрываем файл


} // Конец блока "Чтение данных из файла"



// Печать графа:
void graph_print(int* number_of_vertices, int*** adjacency_matrix) {


    cout << "\n-------------------------------------- Печать графа ------------------------------------------\n";


    // -------------------------------------
    // ---------- 1: Число вершин ----------
    // -------------------------------------


    // Печать числа вершин графа (шапка):
    cout << "\n) Число вершин графа: ";
    

    // Печать числа вершин графа (данные):
    cout << *number_of_vertices;



    // -------------------------------------
    // ------- 2: Матрица смежности --------
    // -------------------------------------


    // Печать матрицы смежности графа (шапка):
    cout <<"\n\n) Матрица смежности графа:\n";


    // Печать матрицы смежности графа (данные):
    for (int i = 0; i < *number_of_vertices; i++) { // Цикл по строкам


        for (int j = 0; j < *number_of_vertices; j++) { // Цикл по столбцам


            // Печать очередного элемента матрицы смежности:
            cout << *(*(*adjacency_matrix + i) + j) << "\t";


        } // Конец блока "Цикл по столбцам"


        cout << endl; // Перенос строки в консоли; ставится, когда допечаталась строка матрицы смежности


    } // Конец блока "Цикл по строкам" и "Печать матрицы смежности графа (данные)"


    cout << "\n----------------------------------------------------------------------------------------------\n";


} // Конец блока "Печать графа"



// Поиск кратчайшего пути между двумя вершинами графа (Дейкстра):
void graph_dijkstra(int* number_of_vertices, int*** adjacency_matrix, int start, int end) {


  
    cout << "\n-------------------------- Поиск кратчайшего пути (Дейкстра) ---------------------------------\n";



    // -------------------------------------
    // ---- 1: Поиск кратчайшего пути ------
    // -------------------------------------



    // Объявление переменных:
    int* d = new int[*number_of_vertices]; // Минимальные расстояния от начальной вершины до всех остальных вершин
    int* v = new int[*number_of_vertices]; // Посещенные вершины (1 - не посещали, 0 - посещали)
    int closest_vertex; // Индекс вершины ближайшей к данной
    int shortest_distance; // Расстояние до ближайшей из вершин 


    // Инициализация массивов расстояний и посещений:
    for (int i = 0; i < *number_of_vertices; i++){


        d[i] = INT_MAX; // По началу все вершины считаем "бесконечно" удаленными


        v[i] = 1; // По началу ни одна вершина не посещена (1 - не посещена, 0 - посещена)


    }


    // Отмечаем посещенной начальную вершину:
    d[start] = 0; 


    // Основная часть алгоритма Дейкстры:
    do {


        // По началу ближайшая вершина не определена:
        closest_vertex = INT_MAX;


        // По началу расстояние до ближайшей вершины не определено:
        shortest_distance = INT_MAX;


        // Перебираем все вершины, чтобы найти ближайшую и расстояние до нее:
        for (int i = 0; i < *number_of_vertices; i++) { 
            

            // Если вершину ещё не посещали и она ближе других вершин к данной:
            if ((v[i] == 1) && ((d[i] < shortest_distance) || shortest_distance == INT_MAX)){
                

                // Эта i-ая вершина теперь ближайшая к данной:
                closest_vertex = i;

                
                // Расстояние до этой i-ой вершины - кратчайшее:
                shortest_distance = d[i];
                
            
            } // Конец блока "Если вершину ещё не посещали и она ближе других вершин к данной"


        } // Конец блока "Перебираем все вершины, чтобы найти ближайшую и расстояние до нее"


        // Если нашли необойденную вершину:
        if (closest_vertex != INT_MAX){


            // Перебираем все вершины графа:
            for (int i = 0; i < *number_of_vertices; i++){


                // Рассматриваем расстояние от ближайшей вершины до i-ой вершины графа:
                int a = *(*(*adjacency_matrix + closest_vertex) + i);
                
                
                // Если путь между ближайшей вершиной и i-ой вершиной существует:
                if (a != 0){


                    // Если пройти через выбранную вершину до i-ой выгоднее, чем ранее известное расстояние до i-ой вершины:
                    if (shortest_distance + a < d[i]){


                        // Определяем более короткое расстояние до i-ой вершины:
                        d[i] = shortest_distance + a;


                    } // Конец блока "Если пройти через выбранную вершину до i-ой выгоднее, чем ранее известное расстояние до i-ой вершины"


                } // Конец блока "Если путь между ближайшей вершиной и i-ой вершиной есть"


            } // Конец блока "Перебираем все вершины графа"


            v[closest_vertex] = 0;


        } // Конец блока "Если нашли необойденную вершину"


    } while (closest_vertex < INT_MAX); // Конец блока "Основная часть алгоритма Дейкстры"


    // Вывод кратчайших расстояний от начальной вершины до остальных:
    cout << "\n\nКратчайшие расстояния от вершины " << start << " до остальных вершин:\n";
    for (int i = 0; i < *number_of_vertices; i++) {


        // Печать очередного расстояния:
        cout << d[i] << " ";


    }


    cout << "\n\nКратчайшее расстояние от вершины " << start << " до " << end << " - " << d[end] << endl;
       


    // ------------------------------------------
    // --- 2: Восстановление кратчайшего пути ---
    // ------------------------------------------



    // Объявление переменных:
    int* visited_vertices = new int[*number_of_vertices]; // Массив посещенных вершин
    visited_vertices[0] = end + 1; // В начале массива посещенных элементов будет стоять конечная вершина
    int k = 1; // Число вершин в массиве посещенных вершин
    int weight = d[end]; // Длиная кратчайшего пути от начальной вершины до конечной 


    // Пока не передвинули метку конца графа к началу:
    while (end != start) {
        

        // Перебираем все вершины:
        for (int i = 0; i < *number_of_vertices; i++) {
            
            
            // Расстояние от i-ой вершины до конечной:
            int distance_from_i_to_end = *(*(*adjacency_matrix + i) + end);


            // Если есть путь от i-ой вершины до конечной:
            if (distance_from_i_to_end != 0){


                // Если путь от i до end является частью кратчайшего пути от start до end:
                if (weight - distance_from_i_to_end == d[i]){


                    // Сохраняем новый вес
                    weight = weight - distance_from_i_to_end; 


                    // Сдвигаем метку конца на i-ую вершину:
                    end = i;


                    // Делаем запись в массив посещеных вершин:
                    visited_vertices[k] = i + 1; 
                    k++;


                }
            
            
            } // Конец блока "Если есть путь от i-ой вершины до конечной"


        } // Конец блока "Перебираем все вершины"


    } // Конец блока "Пока не передвинули метку конца графа к началу"


    // Вывод пути (шапка):
    cout << "\nВывод кратчайшего пути\n";


    // Вывод пути (сами данные):
    for (int i = k-1; i >= 0; i--) {


        // Вывод очередной вершины кратчайшего пути:
        cout << visited_vertices[i] - 1 << " ";


    } // Конец блока "Вывод пути (сами данные)"


    cout << "\n----------------------------------------------------------------------------------------------\n";


} // Конец блока "Поиск кратчайшего пути между двумя вершинами графа (Дейкстра)"



// Функция лишения ребр графа ориентации (граф становится неориенинтированным):
void graph_make_undirected(int* number_of_vertices, int*** adjacency_matrix) {


    // Перебор строк матрицы смежности:
    for (int i = 0; i < *number_of_vertices; i++) {


        // Перебор столбцов матрицы смежности:
        for (int j = 0; j < *number_of_vertices; j++) {


            // Если [i][j] элемент не равен нулю, копируем его в [j][i]:
            if (*(*(*adjacency_matrix + i) + j) != 0) {


                *(*(*adjacency_matrix + j) + i) = *(*(*adjacency_matrix + i) + j);


            } // Если [i][j] элемент равен нулю, копируем [j][i] в [i][j]:
            else {


                *(*(*adjacency_matrix + i) + j) = *(*(*adjacency_matrix + j) + i);


            }
            


        } // Конец блока "Перебор столбцов матрицы смежности"


    } // Конец блока "Перебор строк матрицы смежности"


} // Конец блока "Функция лишения ребр графа ориентации (граф становится неориенинтированным)"



// Построение остовного дерева минимальной стоимости (Прима)
void graph_build_spanning_tree(int* number_of_vertices, int*** adjacency_matrix) {


        cout << "\n------------- Построение остовного дерева минимальной стоимости (Прима) ----------------------\n";

        
        // Объявление переменных:
        int number_of_selected_vertices; // Число уже добавленных в дерево вершин вершин
        int* selected_vertices = new int[*number_of_vertices]; // Массив, где отмечается, какие вершины уже были добавлены в дерево
        int** tree_adjacency_matrix = new int* [*number_of_vertices]; // Матрица смежности остовного дерева


        // Выделим память под матрицу смежности дерева (под столбцы): 
        for (int i = 0; i < *number_of_vertices; i++) {


            // Выделение памяти в i-ой строке:
            tree_adjacency_matrix[i] = new int[*number_of_vertices];


        } // Конец блока "Выделим память под матрицу смежности дерева (под столбцы)"


        // Заполним нулями матрицу смежности дерева:
        for (int i = 0; i < *number_of_vertices; i++) { // Перебор по строкам


            for (int j = 0; j < *number_of_vertices; j++) { // Перебор по столбцам


                // Обнуление очередной ячейки матрицы смежности:
                tree_adjacency_matrix[i][j] = 0;


            } // Конец блока "Перебор по столбцам"


        } // Конец блока "Перебор по строкам" и "Заполним нулями матрицу смежности дерева"


        // По началу ни одна вершина не добавлена в дерево:
        for (int i = 0; i < *number_of_vertices; i++) {


            // Отмечаем очередную вершину графа как еще пока не добавленную в дерево:
            selected_vertices[i] = false;


        } // Конец блока "По началу ни одна вершина не добавлена в дерево"


        // Добавим 0-ую вершину графа в остовное дерево:
        selected_vertices[0] = true;


        // При этом счетчик добавленных в остовное дерево вершин теперь будет показывать единицу:
        number_of_selected_vertices = 1;


        // Выведем заголовок для последующих выводов:
        cout << "\nРебро\t" << ":" << "  Вес" << endl;


        // Перебираем все вершины графа:
        while (number_of_selected_vertices < *number_of_vertices) {


            // Вспомогательные переменные:
            int min = INT_MAX; // Кратчайшее ребро от данного
            int x = 0; // Первая вершина добавляемого в остовное дерево ребра
            int y = 0; // Вторая вершина добавляемого в остовное дерево ребра


            // Перебираем все вершины графа (по i):
            for (int i = 0; i < *number_of_vertices; i++) {


                // Если i-ая вершина уже включена в остовное дерево:
                if (selected_vertices[i]) {


                    // Перебираем вершины графа (по j):
                    for (int j = 0; j < *number_of_vertices; j++) {


                        // Расстояние от i-ой до j-ой вершины:
                        int distance_from_i_to_j = *(*(*adjacency_matrix + i) + j);


                        // Если j-ая вершина не включена в остовное дерево и есть связь между ней и i-ой вершиной:
                        if (!selected_vertices[j] && distance_from_i_to_j) { 


                            // Если ранее найденное минимальное расстояние больше расстояния между i-ой и j-ой вершинами: 
                            if (min > distance_from_i_to_j) {


                                // Обновляем минимальное расстояние:
                                min = distance_from_i_to_j;


                                // Запоминаем ребро между i и j;
                                x = i;
                                y = j;


                            } // Конец блока "Если ранее найденное минимальное расстояние больше расстояния между i-ой и j-ой вершинами"


                        } // Конец блока "Если j-ая вершина не включена в остовное дерево и есть связь между ней и i-ой вершиной"


                    } // Конец блока "Перебираем вершины графа (по j)"


                } // Конец блока "Если i-ая вершина уже включена в остовное дерево"


            } // Конец блока "Перебираем все вершины графа (по i)"

            
            // Выведем информацию о добавленном ребре:
            cout << x << " - " << y << "\t:  " << *(*(*adjacency_matrix + x) + y)  << endl;


            // Запишем информацию о добавленном ребре в матрицу смежности дерева:
            tree_adjacency_matrix[x][y] = min;
            tree_adjacency_matrix[y][x] = min;


            // Выделим добавленную в остовное дерево вершину в соответствующем массиве:
            selected_vertices[y] = true;


            // Счетчик добавленных в дерево вершин увеличивается на единицу:
            number_of_selected_vertices++;


        } // Конец блока "Перебираем все вершины графа"


        // Распечатаем матрицу смежности дерева (шапка):
        cout << "\nМатрица смежности дерева:\n";

        // Распечатаем матрицу смежности дерева (сами данные):
        for (int i = 0; i < *number_of_vertices; i++) { // Перебор по строкам


            for (int j = 0; j < *number_of_vertices; j++) { // Перебор по столбцам


                // Печать очередного элемента матрицы смежности дерева:
                cout << tree_adjacency_matrix[i][j] << "\t";


            } // Конец блока "Перебор по столбцам"


            cout << endl;


        } // Конец блока "Перебор по строкам" и "Заполним нулями матрицу смежности дерева"



        cout << "\n----------------------------------------------------------------------------------------------\n";


} // Конец блока "Построение остовного дерева минимальной стоимости (Прима)"
