# 10833230 李郁含 作業系統 程式作業二
import copy
import queue
import heapq
from functools import total_ordering


class Input_Write_File:
  filename = ''
  def openfile(self, filename):
    self.filename = filename
    f = open(filename + '.txt', "r")
    file = f.read()
    list = file.split() #第一行第一個數字：method 第二個數字：time slice
    method = list[0]    
    timeslice = list[1] 
    list = file.split() #get_processes
    filelist = []
    for p in list[8:]:  #除了前8個，其他全部增加進list
        filelist.append(int(p))
    f.close()
    return int(method), int(timeslice), filelist
  def writefile(self, title, chart, w, t ):
    f = open("out_" + self.filename + ".txt", "w")
    f.write(title)
    f.write(chart)
    f.write(w)
    f.write(t)

class process:
    def __init__(self, id, burst, arrival_time, priority):
        self.id = id
        self.burst = burst
        self.initial_arrival_time = arrival_time
        self.priority = priority
        self.remain_burst = burst
        self.run_times = 0
        self.arrival_time = arrival_time
        self.done_time = 0
        self.check_finish = False
        self.w_time = 0
        self.t_time = 0
        self.response_ratio = 0 # 反應時間比率
    def onetime_later(self):
        self.remain_burst -= 1
        self.run_times = 1
    def update_arrival_time(self, time): # 更新arrival_time
        self.arrival_time = time
    def update_waitting_turnaround_time(self):
        self.t_time =  self.done_time - self.initial_arrival_time # turnaroundtime = donetime - arrivaltime
        self.w_time = self.t_time - self.burst                    # waittingtime = turnaroundtime - arrivaltime
    def update_response_ratio(self, time):  # 更新反應時間比率
        self.t_time =  time - self.initial_arrival_time # turnaroundtime = donetime - arrivaltime
        self.response_ratio =  self.t_time/self.burst
#---------------------------------------------heap--------------------------------------------
@total_ordering
class SRTF_Ready: # 一個以key值為cpu_burst的minHeap
    def __init__(self, remain_key = lambda x:x.remain_burst, arrival_key = lambda x:x.arrival_time):
        self.remain_key = remain_key 
        self.arrival_key = arrival_key 
        self._data = [] 
    def push(self, item):           # key值
        heapq.heappush(self._data, (self.remain_key(item), self.arrival_key(item), item ))
    def pop(self):
        return heapq.heappop(self._data)[2]
    def empty(self):
        if len(self._data) == 0 :
            return True
        else:
            return False
    def __lt__(self, running): # 判斷是否minheap裡面key值最小的process比正running的process還更小
        if self.empty() or running == None: #如果有其中一個是空的就不用比了
            return False
        if self.remain_burst < running.remain_burst:
            return True
        else:
            return False

class PPRR_Ready: # 一個以key值為priority的minHeap
    def __init__(self, priority_key = lambda x:x.priority, arrival_key = lambda x:x.arrival_time):
        self.priority_key = priority_key 
        self.arrival_key = arrival_key 
        self._data = [] 
    def push(self, item):           # key值
        heapq.heappush(self._data, (self.priority_key(item),self.arrival_key(item),item))
    def pop(self):
        return heapq.heappop(self._data)[2]
    def empty(self):
        if len(self._data) == 0 :
            return True
        else:
            return False
    def __lt__(self, running): # 判斷是否minheap裡面key值最小的process比正running的process還更小
        if self.empty() or running == None: #如果有其中一個是空的就不用比了
            return False
        if self._data[0][2].priority < running.priority:
            return True
        else:
            return False

class HRRN_Ready: # 一個以key值為反應時間比率的maxHeap
    def __init__(self, rr_key = lambda x:x.response_ratio, arrival_key = lambda x:x.arrival_time):
        self.rr_key = rr_key 
        self.arrival_key = arrival_key 
        self._data = [] 
    def push(self, item):           # key值 (以負的push進去才會是maxheap)
        heapq.heappush(self._data, (-self.rr_key(item),self.arrival_key(item), item ))
    def pop(self):
        return heapq.heappop(self._data)[2]
    def empty(self):
        if len(self._data) == 0 :
            return True
        else:
            return False
#---------------------------------------------heap--------------------------------------------
class schedule:
    def __init__(self, list):
        self.process_list = list 
        self.time = 0
        self.done_list = []
        self.gantt = []  
    def all_process_done(self): 
        for i in range(len(self.process_list)):
            if not self.process_list[i].check_finish: # 只要有一個process還沒做完就回傳false
                return False
        return True #確認所有process皆已完成
    def update_readyq(self, time, ready): #找到此刻到達的process並丟進ready queue
        for p in self.process_list:
            if p.arrival_time == time:
                ready.put(p)
    def update_donelist(self, p): # 完成的process加入到donelist
        p.done_time = self.time 
        p.check_finish = True 
        p.update_waitting_turnaround_time() 
        self.done_list.append(p)
    def update_gantt(self, id): # 更新甘特圖
        self.gantt.append(id)
#-------------------------------method Schedule--------------------------------------------
class FCFS(schedule): #繼承schedule   #依 ArrivalTime 先後次序進行排程 #non-preemptive
    def start_scheduling(self):
        ready = queue.Queue(0) #宣告一個無限容量的queue 放等待中的process
        running = None 
        while not ready.empty() or not self.all_process_done(): #只要readyqueue還不是空的或還有一個process還沒做完
            self.update_readyq(self.time, ready) #找到此刻到達的process們並丟進ready queue
            if running != None:  # process執行ing
                running.onetime_later()  #先讓他執行完一次
                self.update_gantt(running.id)
                if running.remain_burst <= 0:   # 再確認process是否已執行完
                    self.update_donelist(running) # 完成的process加入到donelist
                    running = None # 設定目前沒有process在執行
            if running == None :  # 沒有正在執行的process：還未有process進去或process皆已做完
                if not ready.empty() :    # 先查看readyqueue有沒有process在等待
                    running = ready.get()
                elif not self.all_process_done(): # 確定不是結束(process皆已做完)且目前這段時間不會有process執行
                  self.update_gantt('-')
            self.time += 1

class RR(schedule):  #依 ArrivalTime 先後次序進行排程 加上 timeslice的限制 #preemptive
    def start_scheduling(self, timeslice):
        ready = queue.Queue(0) #宣告一個無限容量的queue 放等待中的process
        running = None 
        while not ready.empty() or not self.all_process_done() : #只要readyqueue還不是空的或還有一個process還沒做完
            count = timeslice
            while count >= 0:
                self.update_readyq(self.time, ready) #找到此刻到達的process們並丟進ready queue
                if running != None: # process執行ing
                    running.onetime_later()  #先讓他執行完一次
                    self.update_gantt(running.id)
                    if running.remain_burst <= 0: # 再確認process是否已執行完
                        self.update_donelist(running) # 完成的process加入到donelist
                        running = None # 設定目前沒有process在執行
                if running == None or count == timeslice: # 沒有正在執行的process：還未有process進去或process皆已做完
                    if not ready.empty(): # 先查看readyqueue有沒有process在等待
                        running = ready.get()
                        count = timeslice
                    elif not self.all_process_done(): # 確定不是結束(process皆已做完)且目前這段時間不會有process執行
                      self.update_gantt('-')
                elif count == 0: # 此process timeout了！！
                    ready.put(running) #將還未完成的process推進readyq
                    running = ready.get() 
                    count = timeslice
                self.time += 1
                count -= 1

class SRTF(schedule): #依 ArrivalTime 先後次序進行排程 但每次剩餘CPU burst較小的先（沒有timeslice的限制)
    def update_ready(self, time, ready): #覆寫 #preemptive
        for p in self.process_list:
            if p.arrival_time == time:
                ready.push(p)
    def start_scheduling(self):
        ready = SRTF_Ready() #宣告一個無限容量的Heap 放等待中的process
        running = None 
        while not ready.empty() or not self.all_process_done() : #只要readyheap還不是空的或還有一個process還沒做完
            self.update_ready(self.time, ready) #找到此刻到達的process們並丟進ready heap 
            if running != None: # process執行ing
                running.onetime_later() #先讓他執行完一次
                self.update_gantt(running.id)
                if running.remain_burst <= 0: # 再確認process是否已執行完
                    self.update_donelist(running) # 完成的process加入到donelist
                    running = None # 設定目前沒有process在執行
            if running == None: # 沒有正在執行的process：還未有process進去或process皆已做完
                if not ready.empty(): # 先查看readyqueue有沒有process在等待
                    running = ready.pop()
                elif not self.all_process_done(): # 確定不是結束(process皆已做完)且目前這段時間不會有process執行
                    self.update_gantt('-')
            elif ready < running: # 隨著minheap（key:burst)變動，只要有比現在在running的process之burst還要小的話就
                ready.push(running)     #就停止執行此process
                running = ready.pop()   #並換上新的（更小的）
            self.time += 1

class PPRR(schedule): #依 ArrivalTime 先後次序進行排程 但每次priority較小的先（有timeslice的限制)
    def update_ready(self, time, ready):                    #preemptive
        for p in self.process_list:
            if p.arrival_time == time:
                ready.push(p)
    def start_scheduling(self, timeslice):
        ready = PPRR_Ready() #宣告一個無限容量的Heap 放等待中的process
        running = None 
        while not ready.empty() or not self.all_process_done() : #只要readyheap還不是空的或還有一個process還沒做完
            count = timeslice
            while count >= 0:
              self.update_ready(self.time, ready) #找到此刻到達的process們並丟進ready heap 
              if running != None: # process執行ing
                running.onetime_later() #先讓他執行完一次
                self.update_gantt(running.id) 
                if running.remain_burst <= 0: # 再確認process是否已執行完
                    self.update_donelist(running) # 完成的process加入到donelist
                    running = None # 設定目前沒有process在執行
              if running == None or count == timeslice: # 沒有正在執行的process：還未有process進去或process皆已做完
                if not ready.empty(): # 先查看readyqueue有沒有process在等待
                    running = ready.pop()
                    count = timeslice
                elif not self.all_process_done(): # 確定不是結束(process皆已做完)且目前這段時間不會有process執行
                  self.update_gantt('-')
              elif count == 0 or ready < running: # 隨著minheap（key:priority)變動，只要有比現在在running的process之burst還要小的話或timeout了就
                    running.update_arrival_time(self.time) ##更新 arrival time
                    ready.push(running) #就停止執行此process
                    running = ready.pop() #並換上新的（更小的）
                    count = timeslice
              self.time += 1
              count -= 1

class HRRN(schedule): #依 ArrivalTime 先後次序進行排程 但每次反應時間比率較大的先（沒有timeslice的限制)
    def start_scheduling(self):  #non-preemptive
        ready = queue.Queue(0) #宣告一個無限容量的queue 放等待中的process
        running = None 
        while not ready.empty() or not self.all_process_done() : #只要readyqueue還不是空的或還有一個process還沒做完
            self.update_readyq(self.time, ready) #找到此刻到達的process們並丟進ready queue
            if running != None: # process執行ing
                running.onetime_later() #先讓他執行完一次
                self.update_gantt(running.id)
                if running.remain_burst <= 0: # 再確認process是否已執行完
                    self.update_donelist(running) # 完成的process加入到donelist
                    running = None
                    temp_ready = HRRN_Ready() #宣告一個暫時無限容量的Heap 讓ready裡面的data做reheap(max_heap)
                    temp_list = []
                    temp_data = None
                    while not ready.empty(): # 將readyqueue裡面的data全拿出來丟進maxheap每一次去找最大的反應時間比率
                        temp_data = ready.get()
                        temp_data.update_response_ratio(self.time) #一個一個更新反應時間比率
                        temp_list.append(temp_data)
                    temp_list = sorted(temp_list, key = lambda k: k.id) #先以processID先做排序
                    for i in temp_list: # maxheap
                      temp_ready.push(i)
                    while not temp_ready.empty(): #再一個一個推進原本的queue
                      ready.put(temp_ready.pop())
            if running == None: # 沒有正在執行的process：還未有process進去或process皆已做完
                if not ready.empty(): # 先查看readyqueue有沒有process在等待
                    running = ready.get()
                elif not self.all_process_done(): # 確定不是結束(process皆已做完)且目前這段時間不會有process執行
                    self.update_gantt('-')
            self.time += 1
#-------------------------------method Schedule--------------------------------------------
def main():
  filename  = input('請輸入檔案名稱：\n')
  file = Input_Write_File()
  p_method, p_timeslice, filelist = file.openfile(filename) # 讀取 方法 timeslice
  list = []                                                 # 跟之後的ID CPU Burst Arrival Time Priority
  for i in range(int(len(filelist)/4)): #將list裡的每一個分四個丟進process建立process資料
    s = i*4
    myprocess = process(filelist[s],filelist[s+1],filelist[s+2],filelist[s+3])
    list.append(myprocess) #   ID       CPU Burst    Arrival Time    Priority 
  list = sorted(list, key = lambda k: k.id) #先以processID先做排序                                                                     
  if p_method == 1 or p_method == 6: # FCFS or ALL
    list_FCFS = copy.deepcopy(list) #將list deepcopy一份 因為這樣如果list改變，複製品list_FCFS就不會跟著改變
    fcfs = FCFS(list_FCFS)     
    fcfs.start_scheduling()  
    fcfs.done_list = sorted(fcfs.done_list, key = lambda k: k.id) #最後以id排序
  if p_method == 2 or p_method == 6: # RR or ALL
    list_RR = copy.deepcopy(list)
    rr = RR(list_RR)
    rr.start_scheduling(p_timeslice)
    rr.done_list = sorted(rr.done_list, key = lambda k: k.id)  #最後以id排序
  if p_method == 3 or p_method == 6: # SRTF or ALL
    list_SRTF = copy.deepcopy(list)
    srtf = SRTF(list_SRTF)
    srtf.start_scheduling()
    srtf.done_list = sorted(srtf.done_list, key = lambda k: k.id) #最後以id排序
  if p_method == 4 or p_method == 6: # PPRR or ALL
    list_PPRR = copy.deepcopy(list)
    pprr = PPRR(list_PPRR)
    pprr.start_scheduling(p_timeslice)
    pprr.done_list = sorted(pprr.done_list, key = lambda k: k.id) #最後以id排序
  if p_method == 5 or p_method == 6: # HRRN or ALL
    list_HRRN = copy.deepcopy(list)
    hrrn = HRRN(list_HRRN)
    hrrn.start_scheduling()
    hrrn.done_list = sorted(hrrn.done_list, key = lambda k: k.id) #最後以id排序

  title = ''
  if p_method == 1:
      title = 'FCFS'
  elif p_method == 2:
      title = 'RR'
  elif p_method == 3:
      title = 'SRTF'
  elif p_method == 4:
      title = 'Priority RR'
  elif p_method == 5:
      title = 'HRRN'
  elif p_method == 6:
      title = 'All'
  title += '\n'

  method = {1:'FCFS', 2:'RR', 3:'SRTF', 4:'PPRR', 5:'HRRN'}
  gantt = {}
  if p_method == 1 or p_method == 6:
    gantt[1] = fcfs.gantt
  if p_method == 2 or p_method == 6:
    gantt[2] = rr.gantt
  if p_method == 3 or p_method == 6:
    gantt[3] = srtf.gantt
  if p_method == 4 or p_method == 6:
    gantt[4] = pprr.gantt
  if p_method == 5 or p_method == 6:
    gantt[5] = hrrn.gantt
  gantt_chart = ''
  for m in range(1, 6):
    if m == p_method or p_method == 6 :
        gantt_chart += '=={0:>12}==\n'.format(method[m])
        HextoDec = '0123456789ABCDEFGHIJKLMNOPQRSTUVWKYZ'
        for g in gantt[m]:
            if ( g == '-' ) :
              gantt_chart = gantt_chart + '-'
            else :
              gantt_chart += HextoDec[g]
        gantt_chart += '\n'
  gantt_chart += '='*59 + '\n'

  if p_method == 6:
    waiting_time = '\nWaiting Time\n{}\t{}\t{}\t{}\t{}\t{}\n'.format('ID', 'FCFS', 'RR', 'SRTF', 'PPRR', 'HRRN' )
  elif p_method == 1:
      waiting_time = '\nWaiting Time\n{}\t{}\n'.format('ID', 'FCFS')
  elif p_method == 2:
      waiting_time = '\nWaiting Time\n{}\t{}\n'.format('ID', 'RR')
  elif p_method == 3:
      waiting_time = '\nWaiting Time\n{}\t{}\n'.format('ID', 'SRTF')
  elif p_method == 4:
      waiting_time = '\nWaiting Time\n{}\t{}\n'.format('ID', 'PPRR')
  elif p_method == 5:
      waiting_time = '\nWaiting Time\n{}\t{}\n'.format('ID', 'HRRN' )
  waiting_time += '='*59 + '\n'
  for p in range(len(list)):
    waiting_time += '{}\t'.format(list[p].id)
    if p_method == 1 or p_method == 6:
        if p_method == 1:
          waiting_time += '{}'.format(fcfs.done_list[p].w_time)
        elif p_method == 6:
          waiting_time += '{}\t'.format(fcfs.done_list[p].w_time)
    if p_method == 2 or p_method == 6:
        if p_method == 2:
          waiting_time += '{}'.format(rr.done_list[p].w_time)
        elif p_method == 6:
          waiting_time += '{}\t'.format(rr.done_list[p].w_time)
    if p_method == 3 or p_method == 6:
        if p_method == 3:
          waiting_time += '{}'.format(srtf.done_list[p].w_time)
        elif p_method == 6:
          waiting_time += '{}\t'.format(srtf.done_list[p].w_time)
    if p_method == 4 or p_method == 6:
        if p_method == 4:
          waiting_time += '{}'.format(pprr.done_list[p].w_time)
        elif p_method == 6:
          waiting_time += '{}\t'.format(pprr.done_list[p].w_time)
    if p_method == 5 or p_method == 6:
        waiting_time += '{}'.format(hrrn.done_list[p].w_time)
    waiting_time += '\n'
  waiting_time += '='*59 + '\n'

  if p_method == 6:
    turnaround_time = '\nTurnaround Time\n{}\t{}\t{}\t{}\t{}\t{}\n'.format('ID', 'FCFS', 'RR', 'SRTF', 'PPRR', 'HRRN' )
  elif p_method == 1:
      turnaround_time = '\nTurnaround Time\n{}\t{}\n'.format('ID', 'FCFS')
  elif p_method == 2:
      turnaround_time = '\nTurnaround Time\n{}\t{}\n'.format('ID', 'RR')
  elif p_method == 3:
      turnaround_time = '\nTurnaround Time\n{}\t{}\n'.format('ID', 'SRTF')
  elif p_method == 4:
      turnaround_time = '\nTurnaround Time\n{}\t{}\n'.format('ID', 'PPRR')
  elif p_method == 5:
      turnaround_time = '\nTurnaround Time\n{}\t{}\n'.format('ID', 'HRRN' )
  turnaround_time += '='*59 + '\n'
  for p in range(len(list)):
    turnaround_time += '{}\t'.format(list[p].id)
    if p_method == 1 or p_method == 6:
        if p_method == 1:
          turnaround_time += '{}'.format(fcfs.done_list[p].t_time)
        elif p_method == 6:
          turnaround_time += '{}\t'.format(fcfs.done_list[p].t_time)
    if p_method == 2 or p_method == 6:
        if p_method == 2:
          turnaround_time += '{}'.format(rr.done_list[p].t_time)
        elif p_method == 6:
          turnaround_time += '{}\t'.format(rr.done_list[p].t_time)
    if p_method == 3 or p_method == 6:
        if p_method == 3:
          turnaround_time += '{}'.format(srtf.done_list[p].t_time)
        elif p_method == 6:
          turnaround_time += '{}\t'.format(srtf.done_list[p].t_time)
    if p_method == 4 or p_method == 6:
        if p_method == 4:
          turnaround_time += '{}'.format(pprr.done_list[p].t_time)
        elif p_method == 6:
          turnaround_time += '{}\t'.format(pprr.done_list[p].t_time)
    if p_method == 5 or p_method == 6:
        turnaround_time += '{}'.format(hrrn.done_list[p].t_time)
    turnaround_time += '\n'
  turnaround_time += '='*59 + '\n\n'

  file.writefile(title, gantt_chart, waiting_time, turnaround_time ) 
  print('end_test') # test: let me know that it is end 

if __name__ == '__main__':
    print('****************************\n* 0. QUIT                  *\n* 1. OS_HW2                *\n****************************') 
    command = int(input('Input a choice(0, 1): '))
    while command == 1:
      main()
      command = int(input('Input a choice(0, 1): '))
      if command == 0:
        break