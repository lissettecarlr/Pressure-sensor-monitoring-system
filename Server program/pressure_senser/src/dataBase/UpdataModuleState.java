package dataBase;

import java.sql.SQLException;

public class UpdataModuleState {
	public static void Updata(int warningMdule,int state)
	{
		DBhelper db = new DBhelper();
		String sqlexcu = null;

         try {
         sqlexcu = "update BedState set State=? where Bed=?";
         db.preState = db.con.prepareStatement(sqlexcu);
		 db.preState.setInt(2, warningMdule);
		 
		 if(state ==1)
			 db.preState.setString(1,"ON");
		 else
			 db.preState.setString(1,"OFF"); 
			
		 int i=  db.preState.executeUpdate(); 
		 if(i==0)
			 System.out.println("修改失败，模块是："+ warningMdule );
		 else
			 System.out.println("修改成功，模块是："+ warningMdule ); 
         }
    	catch (SQLException e) {
        e.printStackTrace();
        
    	}
        
		try {
			db.sql.close();
			db.con.close();	
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
         
	}
}
