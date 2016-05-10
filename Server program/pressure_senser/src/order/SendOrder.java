package order;

import Tool.dataTransform;

public class SendOrder {
	
		static public byte[] SendLicense(int bedNumber,int order)
		{
			
			byte [] temp1 = dataTransform.intToByteGroup(bedNumber,1);
			byte [] temp2 = dataTransform.intToByteGroup(order,1);
			byte[] license = new byte[5];
			license[0] = (byte) 0xaa;
			license[1] = (byte) 0xdd;
			license[2] = temp1[0];
			license[3] = temp2[0];
			license[4] = (byte) 0xff;
			
			return license;
		}


}
