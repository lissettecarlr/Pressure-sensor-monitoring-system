package socket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

import javax.swing.DefaultDesktopManager;

import dataBase.DB_Connection;
import dataBase.InsertBedMsg;
import dataBase.InsertWarningMsg;
import dataBase.UpdataBedState;
import dataBase.UpdataModuleState;
import dataBase.selectModuleState;

public class ReceiveSocket extends Thread{
	Socket socket;
	int getCounter = 0;		//������յ�����ݴ�С
	int bedNumber = 0; //��λ
	int state = 0 ; //
	int order=0;
	int moduleNumber=0;
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
				  InsertBedMsg.insert(bedNumber, state); //插入离床信息
				  UpdataBedState.Updata(bedNumber, state);//更新床铺状态		  
				  
//				  DB.close();
				  getData[0] = 0;  
			  }
			  
			
			  if(getData[0] == -86 && getData[1] == 17) //0xaa����-86
			  {
				  bedNumber =getData[2];
				  order = getData[3];
				  moduleNumber = getData[4];
				  int Modstate = selectModuleState.GetModuleState(moduleNumber);
				  if ( Modstate==1 && order ==1)  //如果表中是报警，而你发送的是报警 则不允许发送
				  {
					  //记录报警信息但不许发送信息
					  InsertWarningMsg.insert(bedNumber, order);
				  }
				  
				  else if (Modstate ==2 && order ==2)  //如果表中是待机，而你发送的是待机 则不允许发送
				  {
					//记录待机信息但不许发送信息
					 InsertWarningMsg.insert(bedNumber, order);
				  }
					  			
				  else {
					  //允许发送且更新表中模块状态
					  InsertWarningMsg.insert(bedNumber, order);
					  UpdataModuleState.Updata(getData[2], getData[3]);
				}
				  getData[0] = 0;  
			  }
			  
			  }
			  
				
			
		} catch (Exception e) {
			e.printStackTrace();//�������д�ӡ�쳣��Ϣ�ڳ����г����λ�ü�ԭ��
		}
	}
	
}
