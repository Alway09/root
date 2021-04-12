import java.sql.DriverManager;
import java.sql.*;

public class testDB{
  public static void main(String[] argv){
    // Driver load
    System.out.println("Load Driver DB...");
    try{
      Class.forName("org.postgresql.Driver");
    } catch (ClassNotFoundException ce){
      System.out.println("Error");
      ce.printStackTrace();
      System.exit(1);
    }
    System.out.println("OK");
    // Connection
    Connection c=null;
    System.out.println("Connecting...");
    try{
      c=DriverManager.getConnection("jdbc:postgresql://localhost/andy","andy","andypostgres");
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }
    if (c!=null)
      System.out.println("OK");
    else System.out.println("Unknown error");
    // SQL statements
    
    Statement s=null;
    try{
       s=c.createStatement();
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }

    try {
      s.executeUpdate("delete from t");
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }

    try {
      s.executeUpdate("insert into t values(1,'a')");
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }

    try {
      PreparedStatement sp=c.prepareStatement("insert into t values(?,?)");
      sp.setInt(1,2);
      sp.setString(2,"b");
      sp.executeUpdate();
      sp.close();
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }

    try {
      System.out.println("Content table");
      ResultSet r=s.executeQuery("select id,n from t");
      while (r.next())
      {
        System.out.println(r.getString(1)+" "+r.getString(2));
      }      
    } catch (SQLException se){
      System.out.println("Error");
      se.printStackTrace();
      System.exit(1);
    }
  }
}
