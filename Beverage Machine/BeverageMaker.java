package assignment2;
abstract class BeverageMaker {
    public void boilWater() {
      System.out.println("煮水");
    }
    public abstract void brew();
    public void pourInCup() {
      System.out.println("倒進杯子");
    }
    public abstract void addIce();
    public abstract void addCondiments() ;
    final void prepare() {
      boilWater();     // 步驟1
      brew();          // 步驟2
      pourInCup();     // 步驟3
      addIce();        // 步驟4
      addCondiments(); // 步驟5
    }  
  }
