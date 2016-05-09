package dataBase;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.*;

public class DB_Connection {
	String Connection="jdbc:mysql://localhost:3306/RY?"+
			"user=root&password=123456&characterEncoding=UTF8";
	String uri = "jdbc:mysql://localhost:3306/RY?";
	String user = "user=root&password=123456&characterEncoding=UTF8";
	
	 String connet = "jdbc:mysql://120.27.119.115:3306/RY?"
             + "user=root&password=123456&useUnicode=true&characterEncoding=UTF8";
	 
	String inSql = null;
	java.sql.Connection conn = null;
	java.sql.Statement stmt =null;
	
	public DB_Connection()
	{
		//注册驱动
		try {  
            Class.forName("com.mysql.jdbc.Driver");  
        } catch (ClassNotFoundException e) {  
        	System.out.println("Broken driver");
            e.printStackTrace();  
        }  
		//创建连接
		 try {
			 conn = DriverManager.getConnection(connet);
			 //获取表达式
			 stmt= conn.createStatement();
			 
		} catch (SQLException e) {
			System.out.println("Broken conn");
			e.printStackTrace();
		}
		 		
	}
	
	public void insert_bed_state(int bedNumber,int state)
	{
		 Date date = new Date();//获得系统时间.
         String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);//将时间格式转换成符合Timestamp要求的格式.
         Timestamp Dtime = Timestamp.valueOf(nowTime);//把时间转换
         
		 if(state ==1)
			 inSql = "insert into message(bed_Number,state,Dtime) values('" + bedNumber + "','back','" + Dtime + "')";
		 else {
			 inSql = "insert into message(bed_Number,state,Dtime) values('" + bedNumber + "','leave','" + Dtime + "')";
		}
		 try {
			stmt.executeUpdate(inSql);
		} catch (SQLException e) {
			System.out.println("Broken insert");
			e.printStackTrace();
		} 
		 
	}
	
	//床位报警状态(记录下床位状态，是报警，还是非报警，对表进行修改)
	public void SetBedWarningState(int bedNumber,int state) {
		
	}
	
	//得到当前是否有床位处于报警状态
	public boolean GetNowBedWaringState() {
		
		return false;
	}
	
	public void close()
	{
	    try {
			 stmt.close();
			 conn.close(); 
		} catch (SQLException e) {
			System.out.println("Broken close");
			e.printStackTrace();
		}  
	}
	
	
}
