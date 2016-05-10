package dataBase;

import java.sql.SQLException;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Date;

public class InsertWarningMsg {

	public static void insert(int bedNumber , int order)
	{
		DBhelper db = new DBhelper();
		String sqlexcu = null;
		
		Date date = new Date();
		String nowTime = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);
		Timestamp Dtime = Timestamp.valueOf(nowTime);
		 
		 
		 try {
			 sqlexcu = "insert into warning(bedNumber,warningState,setTime) values(?,?,'" + Dtime + "')";
	         db.preState = db.con.prepareStatement(sqlexcu);
			 db.preState.setInt(1, bedNumber);	 
			 
			 if(order ==1)
				 db.preState.setString(2,"warning");
			 else
				 db.preState.setString(2,"standby"); //dai ji
				 
			 int i=  db.preState.executeUpdate(); //执行sql语句 返回成功的条数
			 if(i==0)
				 System.out.println("命令添加失败");
			 else
				 System.out.println("命令添加成功");
	         }
	    	catch (SQLException e) {
	        e.printStackTrace();
	        
	    	}
		 
		 try {
				db.sql.close();
				db.con.close();	
//				rs.close();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}
}
