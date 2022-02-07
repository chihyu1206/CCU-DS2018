資料結構作業二
Environment:Ubuntu 18.04.1
指令: make
input:infix.txt
output:postfix.txt

1.首先先定義兩種struct：stack是用來實作infix to postfix需要的堆疊，所以裡頭使用char的data type；eval_stack則用來實作evaluate the postfix expression，所以照題目投影片的建議使用double float。

2.接著while loop從infix.txt讀入資料，因為每個測資裡的數不只一個digit，用兩個if判斷是否下個字元也是digit，否則輸出空格隔開。

3.接著處理operator的問題，首先判斷如果stack為空就直接push無須比較，不是的話先處理加減乘除，假如push進去的operator優先度大於top的就push進去，小於等於則先pop出top再push進去。

4.接著處理括號的問題，假如是左括號就無條件push進去，如果是右括號就開一個while loop，在遇到前個左括號前將所有stack中的operator都pop出來，最後再把左括號的stack單獨free掉不做輸出。

5.最後再把剩餘的stack都pop出來清空。

6.接著實作evaluate postfix expression的部分，由前個實作順便儲存的陣列讀入postfix格式的字串，只要是數字就push進去，遇到運算子就把最上頭的兩個stack pop出來運算，結果再push回去，最後如果postfix expression的格式沒問題，stack只會剩下一個就是結果。

(因為沒理解作業ppt裡頭第四行測資的規則，所以只有確認前三個的結果沒問題)