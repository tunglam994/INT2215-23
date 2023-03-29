#include <bits/stdc++.h>
using namespace std;
int main ()
{
	int a = 7;
    int* p = &a;
    delete p;
	return 0;
}

// giá trị con trỏ p không được tạo từ biểu thức new int nên sau khi xóa có thể gây ra lỗi hành vi chương trình là không xác định
