package Tool;


public class dataTransform {
	/**
	 * 将byte数组转换为int,若数组为null或者长度为0，返回0
	 */
	public static int byteGroupToInt(byte[] b) {
		if (b != null) {
			int value = 0;
			// 由高位到低位
			for (int i = 0; i < b.length; i++) {
				int shift = (b.length - 1 - i) * 8;
				value += (b[i] & 0x000000FF) << shift;// 往高位游
			}
			return value;
		}
		return 0;
	}
	
	/** int转byte **/
	public static byte[] intToByteGroup(int i, int len) {
		if (len <= 0)
			return null;
		byte[] data = new byte[len];
		for (int x = 0; x < len; x++) {
			data[x] = (byte) (i >> (8 * (len - x - 1)));
		}
		return data;
	}
	
	final protected static char[] hexArray = "0123456789ABCDEF".toCharArray();
	/**
	 * 转换byte[]为hex字符串
	 * 
	 * @param bytes
	 *            要转换的byte数组
	 */
	public static String bytesToString(byte[] bytes) {
		if (bytes == null || bytes.length == 0)
			return null;
		char[] hexChars = new char[bytes.length * 2];
		for (int j = 0; j < bytes.length; j++) {
			int v = bytes[j] & 0xFF;
			hexChars[j * 2] = hexArray[v >>> 4];
			hexChars[j * 2 + 1] = hexArray[v & 0x0F];
		}
		return new String(hexChars);
	}
	/**
	 * String转byte[]数组
	 * 
	 * @param s
	 * @return
	 */
	public static byte[] StringToBytes(String s) {
		String s2;
		byte[] b = new byte[s.length() / 2];
		int i;
		for (i = 0; i < s.length() / 2; i++) {
			s2 = s.substring(i * 2, i * 2 + 2);
			b[i] = (byte) (Integer.parseInt(s2, 16) & 0xff);
		}
		return b;
	}
		
	/**
	 * 取得当前时间戳（精确到秒）
	 * @return
	 */
	public static String timeStamp(){
		long time = System.currentTimeMillis();
		String t = String.valueOf(time/1000);
		return t;
	}
}
