package assignment2;

  public class Main {
    public static void main(String[] args) {
      System.out.println("-------------建立各種飲料製作機-------------");
      BeverageMaker b1 = new CoffeeMaker();
      BeverageMaker b2 = new TeaMaker();
      BeverageMaker b3 = new MilkMaker();
      System.out.println("--------------客人來點了杯咖啡--------------");
      System.out.println("--------------咖啡製作ing--------------");
      b1.prepare();
      System.out.println("--------------客人來點了杯茶--------------");
      System.out.println("--------------茶製作ing--------------");
      b2.prepare();
      System.out.println("--------------客人來點了杯牛奶--------------");
      System.out.println("--------------牛奶製作ing--------------");
      b3.prepare();
    }
  }