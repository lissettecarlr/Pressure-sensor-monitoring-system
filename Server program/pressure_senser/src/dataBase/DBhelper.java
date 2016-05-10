package dataBase;

import java.sql.DriverManager;
import java.sql.SQLException;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class DBhelper {
	public java.sql.Connection con =null;
	public java.sql.Statement sql =null;
	public java.sql.PreparedStatement preState = null;

	public DBhelper(){
		try{
			Class.forName("com.mysql.jdbc.Driver");
		}
		catch(ClassNotFoundException e){
			System.out.println("DB驱动异常 ： "+e);
		}
		//以下为数据库连接
		String uri=DBinfo.getUri();
		String dblogName=DBinfo.getLoginName();
		String dbpassword=DBinfo.getPassword();
		try {
			con=DriverManager.getConnection(uri,dblogName,dbpassword);
			sql=con.createStatement();
				
		} catch (SQLException e) {
			e.printStackTrace();
			System.out.println("连接失败 ： "+e);
		}
	}
}
