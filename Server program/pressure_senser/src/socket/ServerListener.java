package socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JOptionPane;


public class ServerListener  extends Thread{
	public void run() {
		try {
			ServerSocket serverSocket = new ServerSocket(9999); //端口
			while(true){
				//每当有一个客服端连接就有一个socket
				Socket socket =  serverSocket.accept();//阻塞
				System.out.println("有客服端链接-------");
				ReceiveSocket cs = new ReceiveSocket(socket);//新线程
				cs.start();       	
			}
		} catch (IOException e) {
			e.printStackTrace();
		} 
	}
}
