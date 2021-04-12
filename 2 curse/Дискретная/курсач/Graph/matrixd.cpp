#include "matrixd.h"
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<QString>
#include<QPair>

MatrixD::MatrixD(QVector<QVector<QPair<int, QString>>> m, QVector<int> t_s, QVector<int> t_c)
    : matrix(m), table_s(t_s), table_c(t_c)
{
}

void MatrixD::reduction(int h, int k){
    if(h < matrix.size() && k < matrix.size()){
        if(!table_s.isEmpty())
        {
            table_s.remove(h);
        }
        if(!table_c.isEmpty())
        {
            table_c.remove(k);
        }

        for(int i = 0; i < matrix.size(); i++){
            for(int j = k; j < matrix.size()-1; j++){
                matrix[i][j] = matrix[i][j+1];
            }
        }
        for(int i = h; i < matrix.size()-1; i++){
            for(int j = 0; j < matrix.size(); j++){
                matrix[i][j] = matrix[i+1][j];
            }
        }

        if(!matrix.isEmpty()){
            for(int i = 0; i < matrix.size(); i++){
                matrix[i].remove(matrix.size() - 1);
            }
            matrix.remove(matrix.size() - 1);
        }
    }
}

QPair<int, int> MatrixD::edge(){
    int min_s = std::numeric_limits<int>::max(), min_c = std::numeric_limits<int>::max(), max_r = std::numeric_limits<int>::min(), max_r_i;
    QVector<QPair<int,int>> index;
    QVector<int> rating;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j].second != "inf" && matrix[i][j].first == 0){
                for(int k = 0; k < matrix.size(); k++){
                    if(matrix[i][k].second != "inf" && k != j)
                        min_s = std::min(min_s, matrix[i][k].first);
                }
                if(min_s == std::numeric_limits<int>::max()){
                    min_s = 0;
                }
                for(int k = 0; k < matrix.size(); k++){
                    if(matrix[k][j].second != "inf" && k != i)
                        min_c = std::min(min_c, matrix[k][j].first);
                }
                if(min_c == std::numeric_limits<int>::max()){
                    min_c = 0;
                }
                rating.push_back(min_c+min_s);
                index.push_back({i, j});
                min_s = std::numeric_limits<int>::max();
                min_c = std::numeric_limits<int>::max();
            }
        }
    }

    for(int i = 0; i < rating.size(); i++){
        if(rating[i] > max_r){
            max_r = rating[i];
            max_r_i = i;
        }
    }

    return index[max_r_i];
}

int MatrixD::sum_of_const(){
    int subtractingSum = 0, min_c = std::numeric_limits<int>::max(), min_s = std::numeric_limits<int>::max();

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j].second != "inf"){
                min_s = std::min(min_s, matrix[i][j].first);
            }
        }
        if(min_s == std::numeric_limits<int>::max()){
            min_s = 0;
        }
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j].second != "inf"){
                matrix[i][j].first -= min_s;
            }
        }
        subtractingSum += min_s;
        min_s = std::numeric_limits<int>::max();
    }

    for(int j = 0; j < matrix.size(); j++){
        for(int i = 0; i < matrix.size(); i++){
            if(matrix[i][j].second != "inf"){
                min_c = std::min(min_c, matrix[i][j].first);
            }
        }
        if(min_c == std::numeric_limits<int>::max()){
            min_c = 0;
        }
        for(int i = 0; i < matrix.size(); i++){
            if(matrix[i][j].second != "inf"){
                matrix[i][j].first -= min_c;
            }
        }
        subtractingSum += min_c;
        min_c = std::numeric_limits<int>::max();
    }

    return subtractingSum;
}

size_t MatrixD::get_matrix_size() const{
    return matrix.size();
}

void MatrixD::inf_return_trip(){

    if(!path.isEmpty()){
        for(int i = 0; i < table_s.size(); i++){
            if(table_s[i] == path.last().second) {
                for(int j = 0; j < path.size(); j++){
                    for(int k = 0; k < table_c.size(); k++){
                        if(path[j].first == table_c[k]){
                            matrix[i][k].second = "inf";
                        }
                    }
                }
            }

        }
    }
}

void MatrixD::last_transform(int amount_of_cities){
    int start_point{path[0].first};
    bool path_flag{false}, trash_flag{false}, pop_flag{true};
    QVector<QPair<int,int>> temp, trash, buffer;
    temp.push_back(path[0]);
    QPair<int,int> last(path[0]);;
    while(temp.size() < amount_of_cities){
        for(int j = 0; j < path.size(); j++){
            if(temp.last().second == path[j].first){
                for(int q = 0; q < buffer.size(); q++){
                    if(path[j] == buffer[q]){
                        goto l_exit_2;
                    }
                }
                temp.push_back(path[j]);
                if(temp.last().second == start_point && temp.size() != amount_of_cities){
                    while(pop_flag){
                        if(temp.last() == last){
                            pop_flag = false;
                        } else{
                            temp.pop_back();
                        }
                    }
                    while(!buffer.isEmpty()){
                        path.push_back(buffer.last());
                        buffer.pop_back();
                    }
                    pop_flag = true;
                    temp.pop_back();
                    trash.push_back(last);
                } else{
                    buffer.push_back(temp.last());
                    path.remove(j);
                    path_flag = true;
                    break;
                }
            }
            l_exit_2:;
        }
        if(!path_flag){
            for(int k = 0; k < table_s.size(); k++){
                if(table_s[k] == temp.last().second){
                    for(int l = 0; l < table_c.size(); l++){
                            for(int m = 0; m < trash.size(); m++){
                                if(table_s[k] == trash[m].first && table_c[l] == trash[m].second){
                                    trash_flag = true;
                                }
                            }
                            if(!trash_flag){
                                last = {table_s[k], table_c[l]};
                                temp.push_back(last);
                                if(temp.last().first == temp.last().second){
                                    trash.push_back(last);
                                    temp.pop_back();
                                    goto l_exit_1;
                                }
                                if(temp.size() == amount_of_cities && last.second != start_point){
                                    trash.push_back(last);
                                    temp.pop_back();
                                    goto l_exit_1;
                                }
                                for(int t = 0; t < temp.size()-1; t++){
                                    if(temp.last().second == temp[t].first && temp.size() != amount_of_cities){
                                        trash.push_back(last);
                                        temp.pop_back();
                                        goto l_exit_1;
                                    }
                                }
                                goto l_exit_1;
                            }
                            trash_flag = false;
                    }
                }
            }
        }
l_exit_1:
        path_flag = false;
        trash_flag = false;
    }

    path = temp;
}

void MatrixD::add_inf(int h, int k){
    if(h < matrix.size() && k < matrix.size()){
        matrix[h][k].second = "inf";
    }
}

int MatrixD::get_str_num(int n) const {
    if(n < table_s.size()){
        return table_s[n];
    } else{
        std::cout << "MatrixD : get_str_num: index out of range\n";
        exit(1);
    }
}

int MatrixD::get_col_num(int n) const {
    if(n < table_c.size()){
        return table_c[n];
    } else{
        std::cout << "MatrixD : get_col_num: index out of range\n";
        exit(1);
    }
}

bool MatrixD::check_path_right() const{
    bool flag{true};
    if(!path.isEmpty()){
        QVector<QPair<int,int>> temp;
        for(int k = 0; k < path.size(); k++){
            temp.push_back(path[k]);
            for(int i = 0; i < path.size(); i++){
                for(int j = 0; j < path.size(); j++){
                    if(temp.last().second == path[j].first){
                        temp.push_back(path[j]);
                        if(temp.first().first == temp.last().second){
                            flag = false;
                            return flag;
                        }
                    }
                }
            }
            temp.clear();
        }
    }
    return flag;
}

bool MatrixD::all_inf() const{
    int count1 = 0, count2 = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j].second == "inf"){
                count1++;
            }
            count2++;
        }
    }
    if(count1 == count2){
        return true;
    } else{
        return false;
    }
}

void MatrixD::add_to_path(QPair<int, int> p){
    path.push_back(p);
}

void MatrixD::set_bottomLimit(int b_l){
    bottomLimit = b_l;
}

int MatrixD::get_bottomLimit() const{
    return bottomLimit;
}

QPair<int, QString> MatrixD::get_data(int i, int j) const{
    return matrix[i][j];
}

void MatrixD::set_data(int i, int j, int x){
    matrix[i][j].first = x;
}

void MatrixD::set_data(int i, int j, QString x){
    matrix[i][j].second = x;
}

QVector<QPair<int,int>> MatrixD::get_path() const{
    return path;
}
