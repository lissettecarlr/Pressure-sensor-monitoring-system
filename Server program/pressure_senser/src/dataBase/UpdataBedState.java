package dataBase;

import java.text.SimpleDateFormat;
import java.util.Date;

import java.sql.*;

public class UpdataBedState {
	
	public static void Updata(int BedNumber,int state)
	{
		DBhelper db = new DBhelper();
		String sqlexcu = null;
//		ResultSet rs = null;
	
//        sqlexcu = "insert into message(bed_Number,state,Dtime) values(?,?,'" + Dtime + "')";
//		
//        db.preState = db.con.prepareStatement(sqlexcu);
//		db.preState.setInt(1, 1);
//		db.preState.setString(2,"back");   
//         sqlexcu = "Select * From parking_spaces where Bed=?";
         try {
         sqlexcu = "update BedState set State=? where Bed=?";
         db.preState = db.con.prepareStatement(sqlexcu);
		 db.preState.setInt(2, BedNumber);
		 
		 if(state ==1)
			 db.preState.setString(1,"back");
		 else
			 db.preState.setString(1,"leave"); 
			 
//		 rs = db.preState.executeQuery(); //执行SQL语句
		 int i=  db.preState.executeUpdate(); //执行sql语句 返回成功的条数
		 if(i==0)
			 System.out.println("修改失败，床位号是："+ BedNumber );
		 else {
			 System.out.println("修改成功" );
		}
         }
    	catch (SQLException e) {
        e.printStackTrace();
        
    	}
        

		try {
			db.sql.close();
			db.con.close();	
//			rs.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
         
	}

	
}
