執行環境:Ubuntu 18.04
編譯指令:make
輸入/輸出檔名:node.txt/link.txt

描述:
1.先由node.txt讀入提示的node數目，建立struct array再存取各點座標及點的序號。(time complexity:O(n))

2.接著因為有距離<=1才能建立link的限制，不確定數量有多少，因此改用linked list以節省空間，跑一個雙迴圈找出所有合格的距離加入list中。(time complexity:O(n^2))

3.因為迴圈的index是由小到大，造成linked list的頭到尾變成由大到小，為了之後輸出和計算方便，用一個while迴圈把next的指標轉向，讓原本的尾變成新的head，再輸出目前所有已建立的link至link.txt。(time complexity:O(n))

4.最後再跑一個雙迴圈去實作ppt提示的algorithm，只有點到有建立連線的兩點距離平方和小於連線平方，就把連線改成一個極大的數(取消)。(time complexity:O(n^2))

5.最後再把剩下符合planar graph的link以及數量印到link.txt，並將兩個檔關閉，結束程式。(time complexity:O(n))