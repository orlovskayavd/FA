#pragma warning(disable:4996)
#include <iostream>
#include <math.h>
#include <string>
#include <cstring>

#define DATA_TYPE double
#define COMMANDS_SIZE 7

class Node {

public:

    DATA_TYPE k;
    DATA_TYPE degree;
    Node* next;

    Node(DATA_TYPE k, DATA_TYPE degree) : k{ k }, degree{ degree } {
        next = nullptr;
    }
    //
    //    void setNext(int k, int degree) {
    //        this->k = k;
    //        this->degree = degree;
    //    }

    Node& operator *= (const Node& right) {
        this->degree += right.degree;
        this->k *= right.k;
        return *this;
    }

    Node& operator * (const Node& right) {
        Node* result = new Node(this->k * right.k, this->degree + right.degree);
        return *result;
    }


};

class List {
private:
    Node* first;
    int size;
public:
    List() {
        first = nullptr;
        size = 0;
    }

    ~List() {
        Node* cur = first;
        for (int i = 0; i < size; ++i) {
            Node* del = cur;
            cur = cur->next;
            delete del;
        }
    }
    //
    //    List(const List &list) {
    //        Node* cur = first;
    //        for (int i = 0; i < list.size; ++i) {
    //            cur = new Node(list.get(i));
    //            *cur = *cur->next;
    //        }
    //        size = list.size;
    //    }

    //    void addToEnd(Node* node) {
    //        Node* cur = first;
    //        if (cur != nullptr) {
    //            while (cur->next != nullptr) cur = cur->next;
    //            cur->next = node;
    //        } else {
    //            first = (Node *) node;
    //        }
    //        size++;
    //    }

    void add(const Node& node, int i) {
        if (size < i) {
            std::cout << "size";
            return;
        }
        Node* a = new Node(node);
        if (i == 0 && size == 0) {
            first = a;

        }
        else if (i == 0) {

            a->next = first;
            first = a;
        }
        else {
            Node* prev = first;
            Node* cur = first->next;
            for (int j = 1; j < i; ++j) {
                prev = cur;
                cur = cur->next;
            }
            a->next = cur;
            prev->next = a;
        }
        size++;
    }

    Node get(int i) const {
        if (i > size) std::cout << "Out of ";
        Node* cur = first;

        for (int j = 0; j < i; ++j) {
            cur = cur->next;
        }
        return *cur;
    }

    void set(const Node& node, int i) {
        Node* cur = first;
        for (int j = 0; j < i; ++j) {
            cur = cur->next;
        }
        cur->degree = node.degree;
        cur->k = node.k;
    }

    Node* pop(int i) {
        Node* result = first;
        if (i == 0) {
            first = first->next;
            size--;
            return result;
        }
        Node* prev = first;
        result = result->next;
        for (int j = 1; j < i; ++j) {
            prev = result;
            result = result->next;
        }

        prev->next = result->next;
        size--;
        return result;
    }

    int getSize() const {
        return size;
    }
};

class Polynomial {
private:
    List data;


public:


    Polynomial& operator= (const Polynomial& right) {
        this->data = List();
        for (int i = 0; i < right.data.getSize(); ++i) {
            Node node = right.data.get(i);
            //            node.next = nullptr;
            node.next = nullptr;
            this->data.add(node, i);
        }
        return *this;
    }

    Polynomial(const Polynomial& polynomial) {
        this->data = List();
        int size = polynomial.data.getSize();
        for (int i = 0; i < size; ++i) {
            Node node = polynomial.data.get(i);
            node.next = nullptr;
            this->data.add(node, i);
        }
    }



    Polynomial() {
        this->data = List();
    }

    ~Polynomial() = default;

    void add(const Node& node) {
        for (int i = 0; i < data.getSize(); ++i) {
            if (node.degree >= data.get(i).degree) {
                if (node.degree == data.get(i).degree) {
                    DATA_TYPE k = data.get(i).k + node.k;
                    data.set(Node(k, node.degree), i);
                }
                else {
                    data.add(node, i);
                }
                if (data.get(i).k == 0) data.pop(i);
                return;
            }
        }
        data.add(node, data.getSize());
    }



    Polynomial eval(Polynomial right) {
        Polynomial result;
        double x = right.data.get(0).k;
        double tmp = 0;
        double r = 0;
        for (int i = 0; i < data.getSize(); ++i) {
            tmp = pow(x, data.get(i).degree);
            r += tmp * data.get(i).k;
        }

        result.add(Node(r, 0));
        return result;
    }

    Polynomial diff() {
        Polynomial result;
        for (int i = 0; i < data.getSize(); ++i) {
            double k = data.get(i).k * data.get(i).degree;
            double degree = data.get(i).degree - 1;
            Node node(k, degree);
            result.add(node);
        }

        return result;
    }



    void print() const {
        for (int i = 0; i < data.getSize(); ++i) {
            if (data.get(i).k == 0) continue;
            if (i != 0 && data.get(i).k > 0) {

                std::cout << "+";
            }
            if (data.get(i).k < 0) {
                if (data.get(i).k == -1)
                    std::cout << "-";
            }
            if (data.get(i).degree == 0 || data.get(i).k == 1 || data.get(i).k == -1 || data.get(i).degree == 1) {
                if (data.get(i).degree == 0) {
                    std::cout << abs(data.get(i).k);
                }
                else if (data.get(i).k == 1 || data.get(i).k == -1) {
                    std::cout << "x^" << data.get(i).degree;
                }
                else if (data.get(i).degree == 1) {
                    std::cout << data.get(i).k << "x";
                }
            }
            else {
                std::cout << data.get(i).k << "x^" << data.get(i).degree;
            }
        }

        std::cout << std::endl;
    }


    Polynomial& operator+=(const Polynomial& right) {
        for (int i = 0; i < right.data.getSize(); ++i) {
            this->add(right.data.get(i));
        }
        return *this;
    }


    Polynomial& operator-=(const Polynomial& right) {
        for (int i = 0; i < right.data.getSize(); ++i) {
            Node node = right.data.get(i);
            node.k *= -1;
            this->add(node);
        }
        return *this;
    }



    Polynomial& operator*=(const Polynomial& right) {
        Polynomial result;
        for (int i = 0; i < this->data.getSize(); ++i) {
            Node left = this->data.get(i);

            for (int j = 0; j < right.data.getSize(); ++j) {
                DATA_TYPE k = left.k * right.data.get(j).k;
                DATA_TYPE degree = left.degree + right.data.get(j).degree;
                result.add(Node(k, degree));
            }
        }
        //        result.simplify();
        *this = result;
        return *this;
    }


    Polynomial& operator/=(const Polynomial& right) {
        Polynomial result;
        Polynomial ost = *this;

        while (ost.data.getSize() != 0 && right.data.getSize() != 0 && ost.data.get(0).degree >= right.data.get(0).degree) {
            DATA_TYPE k = ost.data.get(0).k / right.data.get(0).k;
            DATA_TYPE degree = ost.data.get(0).degree - right.data.get(0).degree;
            Node tmp = Node(k, degree);
            result.data.add(tmp, result.data.getSize());
            for (int i = 0; i < right.data.getSize(); ++i) {
                Node minus = right.data.get(i);
                minus.k = -1 * minus.k;
                ost.add(tmp * minus);
            }
        }

        *this = result;
        return *this;
    }


    Polynomial& operator%=(const Polynomial& right) {
        Polynomial result;
        Polynomial ost = *this;
        while (ost.data.getSize() != 0 && right.data.getSize() != 0 && ost.data.get(0).degree >= right.data.get(0).degree) {
            DATA_TYPE k = ost.data.get(0).k / right.data.get(0).k;
            DATA_TYPE degree = ost.data.get(0).degree - right.data.get(0).degree;
            Node tmp = Node(k, degree);
            result.data.add(tmp, result.data.getSize());
            for (int i = 0; i < right.data.getSize(); ++i) {
                Node minus = right.data.get(i);
                minus.k = -1 * minus.k;
                ost.add(tmp * minus);
            }
        }

        *this = ost;
        return *this;
    }

    bool isNull() {
        return data.getSize() == 0;
    }



    friend Polynomial operator % (const Polynomial& left, const Polynomial& right);
    friend Polynomial operator / (const Polynomial& left, const Polynomial& right);
    friend Polynomial operator + (const Polynomial& left, const Polynomial& right);
    friend Polynomial operator - (const Polynomial& left, const Polynomial& right);
    friend Polynomial operator * (const Polynomial& left, const Polynomial& right);
    friend std::istream& operator >> (std::istream& in, Polynomial& polynomial);
    friend std::ostream& operator << (std::ostream& out, const Polynomial& polynomial);
};

Polynomial operator*(const Polynomial& left, const Polynomial& right) {
    Polynomial tmp = left;
    return tmp *= right;
}

Polynomial operator+(const Polynomial& left, const Polynomial& right) {
    Polynomial tmp = left;
    tmp += right;
    return tmp;
}

Polynomial operator-(const Polynomial& left, const Polynomial& right) {
    Polynomial tmp = left;
    return tmp -= right;
}

Polynomial operator%(const Polynomial& left, const Polynomial& right) {
    Polynomial tmp = left;
    return tmp %= right;
}

Polynomial operator / (const Polynomial& left, const Polynomial& right) {
    Polynomial tmp = left;
    return tmp /= right;
}

std::istream& operator>>(std::istream& in, Polynomial& polynomial) {
    int size = 0;
    in >> size;
    int k = 0;
    int degree = 0;
    for (int i = 0; i < size; ++i) {
        in >> k >> degree;
        polynomial.add(Node(k, degree));
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& polynomial) {
    int size = polynomial.data.getSize();
    out << size;
    for (int i = 0; i < size; ++i) {
        out << " " << polynomial.data.get(i).k << " " << polynomial.data.get(i).degree;
    }
    return out;
}


const char* commands[COMMANDS_SIZE] = {
        "Add", "Sub", "Mult", "Div", "Mod", "Eval", "Diff"
};

Polynomial getPolUpToSep(char* buf, char sep) {
    Polynomial result;
    double k = 0;
    double degree = 0;
    char* b = buf;
    while (*b != sep) {
        if (*b == '-') {
            b++;
            k = -1;
        }
        else {
            if (*b == '+') {
                b++;
            }
            k = 1;
        }
        while (*b != '+' && *b != '-' && *b != sep) {
            if (isdigit(*b)) {
                double tmp = k;
                sscanf(b, "%lf", &k);
                k *= tmp;
                while (*b != '+' && *b != '-' && *b != 'x' && *b != sep && *b != ')') b++;
            }

            if (*b == 'x' && *(b + 1) == '^') {
                b += 2;
                sscanf(b, "%lf", &degree);
                //                if (k < 0) b++;
                while (*b != '+' && *b != '-' && *b != 'x' && *b != sep && *b != ')') b++;
            }
            else if (*b == 'x') {
                degree = 1;
                b++;
            }
            else if (*b != '+' && *b != '-') {
                degree = 0;

            }
            result.add(Node(k, degree));
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    FILE* file;
    if (!(file = fopen(argv[1], "r"))) {
        exit(-1);
    }

    char buf[BUFSIZ], * b = buf;
    char c;
    Polynomial sum;
    while (!feof(file)) {
        fscanf(file, "%c", &c);
        if (feof(file)) break;
        if (c == ' ' || c == '\n') continue;
        if (c == ';') {
            *b = 0;
            int i;
            for (i = 0; i < COMMANDS_SIZE; ++i) {
                if (strstr(buf, commands[i]) == buf) {
                    break;
                }
            }
            b = buf;
            b += strlen(commands[i]) + 1;
            int countOfArg = 0;
            if (strstr(buf, ",")) {
                countOfArg = 2;
            }
            else {
                countOfArg = 1;
            }

            Polynomial left;
            Polynomial right;
            left = getPolUpToSep(b, ')');
            if (countOfArg == 2) {
                left = getPolUpToSep(b, ',');
                while (*b != ',') b++;
                b++;
                right = getPolUpToSep(b, ')');
            }

            if (countOfArg == 1 && i != 6) right = sum;
            switch (i) {
            case 0:
                sum = left + right;
                break;

            case 1:
                sum = left - right;
                break;

            case 2:
                sum = left * right;
                break;

            case 3:
                sum = left / right;
                break;

            case 4:
                sum = left % right;
                break;

            case 5:
                sum = right.eval(left);
                break;

            case 6:
                if (left.isNull()) left = sum;
                sum = left.diff();
                break;
            }

            sum.print();
            b = buf;
        }
        else {
            *b++ = c;
        }
    }
    fclose(file);
}
