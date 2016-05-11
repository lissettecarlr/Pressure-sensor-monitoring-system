package dataBase;

import java.sql.ResultSet;
import java.sql.SQLException;

public class selectModuleState {

	public static int GetModuleState(int moduleNumber)
	{
		
		String state =null;
		DBhelper db = new DBhelper();
		String sqlexcu = null;
		ResultSet rs = null;
		
		sqlexcu = "select * from ModuleState where moduleID=? ";

		try {
			db.preState = db.con.prepareStatement(sqlexcu);
			db.preState.setInt(1, moduleNumber);
			rs = db.preState.executeQuery();
			rs.next(); //查询第一行没有数据
			state = rs.getString("state");
						
			System.out.println("模块当前的状态是" + state );
			
		} catch (SQLException e) {
			System.out.println("查询报错");
			e.printStackTrace();
		}

		
		 
		try {
			db.sql.close();
			db.con.close();	
		} catch (SQLException e) {
			e.printStackTrace();
		}
		
		if(state.equals("ON"))
			return 1;   //预警中
		else
			return 2;  //待机中
	}
}
