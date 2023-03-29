#include <iostream>
using namespace std;

// print address of x
void f(int xval)
{
   int x;
   x = xval;
   // in địa chỉ của x tại đây
   cout << &x << endl;
}
// print address of y
void g(int yval)
{
   int y;
   // in địa chỉ của y tại đây
   cout << &y << endl;
}
int main()
{
   f(7);
   g(11);
   return 0;
}
/* nhận xét: vị trí của stack frame của hai hàm trùng nhau. Do ở hai hàm có cùng kiểu tham số đầu vào, cùng kiểu trả về,
biến x, y trong hàm sau khi chạy xong sẽ được hủy nên khả năng lớn chương trình biên dịch sẽ vị trí cùng nhau.
