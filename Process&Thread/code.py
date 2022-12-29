# 10833230 李郁含 作業系統 程式作業一
import time 
import queue
from threading import Thread
import multiprocessing
from multiprocessing import Process
from datetime import datetime, timedelta, timezone
class Do:
  fileName = ''
  k = 0
  method = ''

  def Readfile(self): # 一行一行將檔案讀進列表
    file = open(self.fileName  + '.txt' , "r") # 讀檔
    line = file.readline() 
    List = list()
    while line:
      List.append(line)
      line = file.readline()
    intList = list(map(int, List)) # 將列表裡的每個字串轉換成數字
    file.close()
    return intList

  def Readfile_To_KList(self):  # 一行一行將檔案讀進列表並切成k份
    list = self.Readfile()      
    step = len(list) // self.k   # 向下取整除法 （切完）每份小list的數量＝大list的數量/要切幾份 
    k_list = [list[i:i+step] for i in range(0, len(list), step)] # 以step數量為一組切成k或k+1個
    if (len(list) % self.k) != 0:  #如果有多餘的（k+1個              (k+1個）因為不一定會剛好切整數
      for i in range(len(k_list[self.k])):   #把k+1那個list裡面的所有數字增加進第k個list
        k_list[self.k-1].append(k_list[self.k][i])
      k_list.pop()   #把最後一個（多餘的那個k+1）刪掉
    return k_list

  def BubbleSort(self, q, list):
    for i in range(len(list)):
      for j in range(0, len(list) - i - 1):
        if list[j] > list[j + 1]:
          temp = list[j]
          list[j] = list[j+1]
          list[j+1] = temp
    q.put(list)

  def MergeSort(self, q, list1, list2): 
    one, two = 0, 0
    newlist = [] # sort完的list --> newlist = list1 + list2  
    while one < len(list1) and two < len(list2): # 只要其中一個list輪到底就break
      if list1[one] <= list2[two]:   #選數字較小的增加進newlist（數字一樣就沒差
        newlist.append(list1[one])
        one = one + 1
      else : 
        newlist.append(list2[two])
        two = two + 1
    while one < len(list1):      #一個一個把list1剩下的（較大的）放進newlist
      newlist.append(list1[one])
      one = one + 1
    while two < len(list2):      #一個一個把list2剩下的（較大的）放進newlist
      newlist.append(list2[two])
      two = two + 1
    q.put(newlist) #最後將合再一起的newlist再重新推進queue

  def bubble_merge(self, q, Klist):# 在一個process內對K份資料進行BubbleSort和MergeSort
    for i in range(self.k): #先一個一個對一份一份（到k份）的list作BubbleSort
        self.BubbleSort(q, Klist[i])
    while q.qsize() >= 2:   #對整份作MergeSort 直到最後都merge在一起變成一份
        one = q.get() 
        two = q.get()
        self.MergeSort(q, one, two)  #兩份兩份作MergeSort

  def WriteFile(self, list, cpu_time): # 一行一行將list裡的數字寫檔
    file = open(self.fileName + '_output'+ self.method +'.txt', "w") ## open a file for writing
    file.write('Sort : \n')
    for i in list:
        file.write(str(i) + '\n')
    file.write('CPU Time : {:.20f}\n'.format(cpu_time))   # 顯示方法 x 的執行時間
    dt1 = datetime.utcnow().replace(tzinfo=timezone.utc)
    writeTime = dt1.astimezone(timezone(timedelta(hours=8)))
    file.write('Output Time : '+str(writeTime))           # 顯示完成方法 x 時，寫檔當下的時間(時區為 UTC+8)
    file.close()

  def method1(self):  # 將N個數目字直接進行BubbleSort,並顯示CPU執行之時間
    list = self.Readfile()   # 一行一行將檔案讀進列表
    start = time.perf_counter() # clock start
    q = queue.Queue(len(list))  # 宣告一個最大容量為list長度的queue(先進先出)
    self.BubbleSort(q, list)     # 直接進行 bubblesort 
    end = time.perf_counter()   # clock end
    CPUtime = end - start 
    self.WriteFile(q.get(), CPUtime)  # 一行一行將list裡的數字寫檔

  def method2(self):  # 將N個數目字切成k份,在一個process內對K份資料進行BubbleSort之後,再用同一個process作MergeSort,並顯示CPU執行之時間
    Klist = self.Readfile_To_KList() # 一行一行將檔案讀進列表並切成k份
    start = time.perf_counter() # clock start
    q = multiprocessing.Manager().Queue(self.k) # 宣告一個共享的最大容量為k長度的queue(先進先出)
    job = Process(target = self.bubble_merge, args = (q, Klist))
    job.start()  #同一個process進行BubbleSort和MergeSort
    job.join()
    end = time.perf_counter()   # clock end
    CPUtime = end - start 
    self.WriteFile(q.get(), CPUtime)

  def method3(self): # 將N個數目字切成k份,並由K個processes分別進行BubbleSort之後,再用process(es)作MergeSort,並顯示CPU執行之時間
    Klist = self.Readfile_To_KList() # 一行一行將檔案讀進列表並切成k份
    jobs = queue.Queue(self.k)
    mjobs = queue.Queue(self.k-1)
    start = time.perf_counter() # clock start
    q = multiprocessing.Manager().Queue(self.k) # 宣告一個共享的最大容量為k長度的queue(先進先出)
    for i in range(self.k): #建立k個processes
      job = Process(target=self.BubbleSort, args=(q, Klist[i]))
      jobs.put(job)
    i = 0
    while 0 < jobs.qsize() or i < self.k - 1: # 只要有一個還沒宣布start就不會break
      if 0 < jobs.qsize(): #k個process分別進行BubbleSort
        jobs.get().start()
      if q.qsize() >= 2: # 只要還有兩份就作MergeSort
        one = q.get()
        two = q.get() # 兩份兩份作MergeSort
        mjob = Process(target=self.MergeSort, args=(q, one, two))
        mjob.start()
        mjobs.put(mjob)
        i = i + 1
    while 0 < jobs.qsize() : # 等所有工作都做完
      jobs.get().join()
    while 0 < mjobs.qsize(): # 等所有工作都做完
      mjobs.get().join()
    end = time.perf_counter()   # clock end
    CPUtime = end - start 
    self.WriteFile(q.get(), CPUtime)

  def method4(self): # 將N個數目字切成k份,並由K個threads分別進行BubbleSort之後,再用thread(s)作MergeSort,並顯示CPU執行之時間
    Klist = self.Readfile_To_KList() # 一行一行將檔案讀進列表並切成k份
    jobs = queue.Queue(self.k)
    mjobs = queue.Queue(self.k-1)
    start = time.perf_counter() # clock start
    q = queue.Queue(self.k) # 宣告一個最大容量為k長度的queue(先進先出)
    for i in range(self.k): #建立k個threads
      job = Thread(target=self.BubbleSort, args=(q, Klist[i]))
      jobs.put(job)
    i = 0
    while 0 < jobs.qsize() or i < self.k - 1: # 只要有一個還沒宣布start就不會break
      if 0 < jobs.qsize(): # k個thread分別進行BubbleSort
        jobs.get().start()
      if q.qsize() >= 2: # 只要還有兩份就作MergeSort
        one = q.get()
        two = q.get()  # 兩份兩份作MergeSort
        mjob = Thread(target=self.MergeSort, args=(q, one, two))
        mjob.start()
        mjobs.put(mjob)
        i = i + 1
    while 0 < jobs.qsize() : # 等所有工作都做完
      jobs.get().join()
    while 0 < mjobs.qsize(): # 等所有工作都做完
      mjobs.get().join()
    end = time.perf_counter()   # clock end
    CPUtime = end - start 
    self.WriteFile(q.get(), CPUtime)

def main():
    do = Do()
    do.fileName = input('請輸入檔案名稱：\n')
    do.k = int(input('請輸入要切成幾份：\n'))                          
    do.method = input('請輸入方法編號：（方法1, 方法2, 方法3, 方法4)\n')

    if do.method == '1':
        do.method1()
    elif do.method == '2':
        do.method2()
    elif do.method == '3':
        do.method3()
    elif do.method == '4':
        do.method4()
    else:
        print('沒有這個方法！！')

    print('end_test') # test: let me know that it is end 

if __name__ == '__main__':
    print('****************************\n* 0. QUIT                  *\n* 1. OS_HW1                *\n****************************') 
    command = int(input('Input a choice(0, 1): '))
    while command == 1:
      main()
      command = int(input('Input a choice(0, 1): '))
      if command == 0:
        break