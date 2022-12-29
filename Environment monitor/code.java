import java.util.ArrayList;

  interface Subject {  //被觀察者
    public void register(Observer customer);    // 註冊  
    public void unregister(Observer customer);  // 取消註冊
    public void notifyCustomers();              // 通知客戶
  } // Subject

  interface Observer {  //觀察者
    void subscribe(Subject environmentData);    // 訂閱
    void unsubscribe();                         // 取消訂閱
    void update();         // 更新
  } // Observer

  class EnvironmentData implements Subject { //環境可以為被觀察者
    private ArrayList<Observer> customerList = new ArrayList<Observer>();  // 建立客戶清單，紀錄已註冊的客戶
    private float temperature = 36 ;           //當資料被更新的時候，管理員就告知所有客戶可以更新的資料
    private int humidity = 2 ;
    private int windSpeed = 15 ;
    public float getTemperature() {
      return temperature;
    } // getTemperature
    public int getHumidity() {
      return humidity;
    } // getHumidity
    public int getWindSpeed() {
      return windSpeed;
    } // getWindSpeed
    public void setMeasurement( float t, int h, int w) {     // 設定EnvironmentData
      this.temperature = t;
      this.humidity = h;
      this.windSpeed = w;
      notifyCustomers();
    } // setMeasurement
    public void register(Observer customer) {        // 註冊客戶
      customerList.add(customer);
    } // register
    public void unregister(Observer customer) {     // 取消註冊客戶
      customerList.remove(customer);
    } // unregister
    public void notifyCustomers() {                 // 通知客戶
      for(Observer customer : customerList){        
        customer.update();
      } // for
    } // notifyCustomers
  }
 
  class Customer implements Observer { //客戶可以為觀察者
    private String name = null;              // 客戶的名稱
    private Subject environmentData = null;  // 訂閱的EnvironmentData
    private boolean needtemp = false;
    private boolean needhumi = false;
    private boolean needwind = false;
    public Customer(String name, boolean t, boolean h, boolean w){
      this.name = name;
      this.needtemp = t;
      this.needhumi = h;
      this.needwind = w;
    } // Customer
    public void subscribe(Subject environmentData) {       // 訂閱EnvironmentData
      this.environmentData = environmentData;
      environmentData.register(this);      // 註冊這個客戶
    } // subscribe
    public void unsubscribe() {          // 取消訂閱
      environmentData.unregister(this);  // 取消註冊這個客戶
    } // unsubscribe
    public void displayTemp(){
      System.out.println("customer " + name + " temperature: " + ((EnvironmentData) this.environmentData).getTemperature());
    } // displayTemp
    public void displayHumi(){
      System.out.println("customer " + name + " humidity: " + ((EnvironmentData) this.environmentData).getHumidity()); 
    } // displayHumi
    public void displayWind(){
      System.out.println("customer " + name + " windSpeed: " + ((EnvironmentData) this.environmentData).getWindSpeed());
    } // displayWind
    public void show(){
      if ( this.needtemp )
        displayTemp();
      if ( this.needhumi )
        displayHumi();
      if ( this.needwind )
        displayWind();
    } // show
    public void update() {      // 更新通知
      show();
    } // update
  }

  public class Main {
    public static void main(String[] args) {
      EnvironmentData environmentData = new EnvironmentData();  // 建立一個環境
      // 建立一些客戶 一開始就紀錄好這個客戶想知道哪些資訊 並訂閱環境讓環境（管理員）知道大家的資訊
      Customer ivy = new Customer("Ivy", false, false, true);      // 客戶Ivy想訂閱環境
      ivy.subscribe(environmentData);
      Customer kevin = new Customer("Kevin", true, false, true);  // 客戶Kevin想訂閱環境
      kevin.subscribe(environmentData);
      Customer penny = new Customer("Penny", true, true, true);  // 客戶Penny想訂閱環境
      penny.subscribe(environmentData);

      // 客戶個別需要的環境資訊
      System.out.println("----------客戶需要的資訊----------");
      ivy.show();
      kevin.show();
      penny.show();

      System.out.println("-------------更新通知-------------");
      environmentData.setMeasurement(52, 16, 32) ;   // 更新環境資訊(EnvironmentData)
      //並通知所有有在環境（管理員）客戶清單的客戶，讓客戶依照自己原本的需求（想知道哪些資訊）決定要取得那些資料
      
      // 客戶Key和penny退訂環境
      environmentData.unregister(kevin) ;
      environmentData.unregister(penny) ;

      // 新客戶Lulu想訂閱環境 一樣一開始就紀錄好這個客戶想知道哪些資訊
      Customer lulu = new Customer("Lulu", false, true, true);
      lulu.subscribe(environmentData);
      // 新客戶Jenny想訂閱環境
      Customer jenny = new Customer("Jenny", true, false, true);
      jenny.subscribe(environmentData);

      System.out.println("-------------更新通知-------------");
      environmentData.setMeasurement(38, 23, 51) ;   // 更新環境資訊(EnvironmentData)
      
    }
  }