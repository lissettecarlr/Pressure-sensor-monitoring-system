package dataBase;


public class DBinfo {
	private static final String loginName="root";
	private static final String password="123456";
	private static final String uri="jdbc:mysql://120.27.119.115:3306/RY";
	
	public static String getLoginName(){
		return loginName;
	}
	public static String getPassword(){
		return password;
	}
	public static String getUri(){
		return uri;
	}
}
