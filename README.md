# Page-Replacement


## 開發平台
Windows 11 

## 開發環境
Visual Studio Code
Win32 MinGW 6.3.0

## 題目說明
自檔案輸入Page Frame個數及各個Page Reference，模擬FIFO、LRU、LFU+LRU、MFU+FIFO、MFU+LRU等不同演算法，同時計算Page Replacement的Page Fault、Page Replace次數。

## 輸入說明
第 1列的第 1個數字為方法 , 方法 1~6
1. FIFO
2. LRU
3. LFU + LRU
4. MFU + FIFO
5. MFU + LRU
6. ALL(都要執行 )

第 1列的第 2個數字為 page frame的個數， 皆為正整數，範圍不定 。

第 2列為 Page Reference的次序。

![image](https://user-images.githubusercontent.com/95240041/194380170-d67b8902-34db-412d-9a24-db4fd246b251.png)


## 輸出範例
![image](https://user-images.githubusercontent.com/95240041/194380488-66008faa-fd51-495f-8843-d423882ae122.png)


## 不同方法的比較
![image](https://user-images.githubusercontent.com/95240041/194380848-eed8a042-07c7-478c-a6a4-da26265ff98a.png)

![image](https://user-images.githubusercontent.com/95240041/194381002-2d1047f6-3b5c-4a42-ba4e-3fbf3c239a0c.png)

![image](https://user-images.githubusercontent.com/95240041/194381061-49bf7811-ffdb-4d4b-b479-edba3756a9c9.png)

![image](https://user-images.githubusercontent.com/95240041/194381092-03be113b-3b70-4380-8e93-a87eac788ee9.png)

## 結果與討論
　　從上方的表格中，可看出input1在Page number由3轉為4時，FIFO、MFU+FIFO及MFU+LRU的Page Fault值上升(黃色表格處)，LRU及LFU+LRU的Page Fault值下降，Page Replacement則正常下降或持平，而Page number由4轉為5時，所有方法Page Fault此時才都降為5，Page Replacement也降為0。而input2不管在Page number由3轉為4或由4轉為5時，Page Fault值皆下降，Page Replacement也正常下降。

畢雷笛反例
  定義：增加Page frame，反而造成更多Page Fault及Page Replacement

　　從上方實驗後得知，input1在Page number由3轉為4時，FIFO、MFU+FIFO及MFU+LRU這三種方法皆會產生畢雷笛反例(即黃色表格處)，但在input2中Page number由3轉為4時，所有方法的Page Fault及Page Replacement皆正常下降，由此可見使用FIFO、MFU+FIFO及MFU+LRU時並不是增加Page frame，就一定能減少Page Fault及Page Replacement，但也並非在所有input下皆會發生畢雷笛反例。

　　經過查詢，許多網站皆說明只有FIFO才有機會遭成畢雷笛反例，而基於STACK原理的方法(如：LRU、Optimal )不會造成畢雷笛反例。而本次實驗結果大致上與上述結論相同，但奇怪的是MFU+LRU竟然發生了畢雷笛反例，思考了許久之後，推測是因為MFU會破壞LRU的STACK原則，因此才會造成基於STACK原理的LRU方法也發生畢雷笛反例。依照這個邏輯加上一段得出的結論(並非在所有input下皆會發生畢雷笛反例)，延伸思考下去，那應該LFU+LRU也有機會產生畢雷笛反例，因為LFU和MFU相同皆有可能打亂LRU的STACK，只是這次的數據下看不出來而已。

　　因此本次作業得到的結論為FIFO加上任何方法都有機會遭成畢雷笛反例(如：FIFO、MFU+FIFO)，而若只是單純的LRU並不會有畢雷笛反例產生，但若與任何有機會打亂STACK原則的方式混合(如：LFU+LRU、MFU+LRU)則也有機會產生畢雷笛反例。


