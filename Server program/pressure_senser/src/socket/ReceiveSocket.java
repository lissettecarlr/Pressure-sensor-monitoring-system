package socket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

import javax.swing.DefaultDesktopManager;

import dataBase.DB_Connection;
import dataBase.InsertBedMsg;
import dataBase.UpdataBedState;

public class ReceiveSocket extends Thread{
	Socket socket;
	int getCounter = 0;		//������յ�����ݴ�С
	int bedNumber = 0; //��λ
	int state = 0 ; //״̬
	
	public ReceiveSocket(Socket s){
		this.socket = s;
	}
	
	public void run()
	{
		try {
			boolean connect = true;						
			byte getData[] = new byte[5];

			InputStream isTemplet = null;
			OutputStream osTemplet = null;
			
			while(true)
			{				
				try {
					osTemplet = socket.getOutputStream();
					isTemplet = socket.getInputStream();
					
				} catch (Exception e) {
					connect = false ;
					System.out.println("Broken A");
					break;
				}
			  if(socket.isConnected())
			  {
					try
					{
						getCounter=isTemplet.read(getData, 0, 5);						
					}
					catch(IOException e)
					{
						e.printStackTrace();
						System.out.println("Broken B");
						connect = false;
						break; 
					}
			  }
			  
			 		  			  
			  if(getData[0] == -86 && getData[1] == -86) 
			  {
				  bedNumber =getData[2];
				  state = getData[3];
				   System.out.println(bedNumber);
				  System.out.println(state);
				  
//				  DB_Connection DB =new DB_Connection();
//				  DB.insert_bed_state(bedNumber, state);
//				  InsertBedMsg.insert(bedNumber, state);
				  UpdataBedState.Updata(bedNumber, state);		  
				  
//				  DB.close();
				  getData[0] = 0;  
			  }
			  
			
			  if(getData[0] == -86 && getData[1] == 17) //0xaa����-86
			  {
				  //����Ƿ����?��
				  //���øô�λ�ı���״̬
				  //������λ���Ƿ��ܸ�Ԥ��ģ�鷢�ͱ�����Ϣ
			  }
			  
			  }
			  
				
			
		} catch (Exception e) {
			e.printStackTrace();//�������д�ӡ�쳣��Ϣ�ڳ����г����λ�ü�ԭ��
		}
	}
	
}
