#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Treap {
    int x, y, size;
    Treap* l, * r;
    Treap(int key) : x(key), y(rand()), l(nullptr), r(nullptr), size(1) {}
    void Update() {
        size = 1 + sz(l) + sz(r);
    }
    friend inline int sz(Treap* t);
};

Treap* Merge(Treap* L, Treap* R) {
    if (L == nullptr || R == nullptr) {
        return (L == nullptr ? R : L);
    }

    if (L->y > R->y) {
        L->r = Merge(L->r, R);
        L->Update();
        return L;
    }

    else {
        R->l = Merge(L, R->l);
        R->Update();
        return R;
    }
}

void Split(Treap* T, int key, Treap*& T1, Treap*& T2) {
    if (T == nullptr) {
        T1 = nullptr;
        T2 = nullptr;
    }
    else if (T->x <= key) {
        Split(T->r, key, T->r, T2);
        T1 = T;
    }
    else {
        Split(T->l, key, T1, T->l);
        T2 = T;
    }
    sz(T);
}

Treap* Insert(Treap* root, int new_key) {
    Treap* T1 = nullptr;
    Treap* T2 = nullptr;
    Split(root, new_key, T1, T2);
    Treap* new_node = new Treap(new_key);
    return Merge(Merge(T1, new_node), T2);
}

Treap* RemoveOne(Treap* root, int key) {
    Treap* T1, * T2, * left, * right;
    Split(root, key, T1, T2);
    Split(T1, key - 1, left, right);
    delete right;
    return Merge(left, T2);
}

bool find(Treap* root, int key) {
    if (root == nullptr) {
        return false;
    }
    if (root->x == key) {
        return true;
    }
    if (root->x < key) {
        return find(root->r, key);
    }
    else {
        return find(root->l, key);
    }
}
inline int sz(Treap* t) {
    return (t ? t->size : 0);
}

int Kth(Treap* root, int k) {
    if (!root) {
        return -2000000000;
    }
    int lsz = sz(root->l);
    if (k == lsz)
        return root->x;
    if (k < lsz) {
        return Kth(root->l, k);
    }
    else {
        return Kth(root->r, k - lsz - 1);
    }
}

int prev(Treap* root, int k) {
    if (!root) {
        return -2000000000;
    }
    Treap* left = nullptr;
    Treap* right = nullptr;
    Split(root, k, left, right);
    if (!left) {
        root = Merge(left, right);
        return -2000000000;
    }
    while (left->r != nullptr) {
        left = left->r;
    }
    root = Merge(left, right);
    return left->x;
}

int next(Treap* root, int k) {
    if (!root) {
        return -2000000000;
    }
    Treap* left = nullptr;
    Treap* right = nullptr;
    Split(root, k, left, right);
    if (!right) {
        root = Merge(left, right);
        return -2000000000;
    }
    while (right->r != nullptr) {
        right = right->r;
    }
    root = Merge(left, right);
    return right->x;

}

int main() {
    string comand;
    string ans;
    Treap* root = nullptr;
    int x;
    while (cin >> comand) {
        cin >> x;
        if (comand == "insert") {
            root = Insert(root, x);
        }
        else if (comand == "delete") {
            root = RemoveOne(root, x);
        }
        else if (comand == "exists") {
            if (find(root, x)) {
                cout << "true" << endl;
            }
            else {
                cout << "false" << endl;
            }
        }
        else if (comand == "kth") {
            int ans = Kth(root, x - 1);
            if (ans != -2000000000) {
                cout << ans << endl;
            }
            else {
                cout << "none" << endl;
            }
        }
        else if (comand == "next") {
            int ans = next(root, x);
            if (ans != -2000000000) {
                cout << ans << endl;
            }
            else {
                cout << "none" << endl;
            }
        }
        else if (comand == "prev") {
            int ans = prev(root, x);
            if (ans != -2000000000) {
                cout << ans << endl;
            }
            else {
                cout << "none" << endl;
            }
        }
    }
    while (sz(root) > 0) {
        root = RemoveOne(root, root->x);
    }

    return 0;
}