package jauler.sensormouse;
import android.util.Log;
import java.io.DataOutputStream;
import java.net.Socket;

/**
 * Created by rytis on 14.12.10.
 */
public class Connector extends Thread {
    String server_addr;
    Integer port;
    Socket socket;
    DataOutputStream out;

    Connector(String address, Integer port_num){
        server_addr = address;
        port = port_num;
    }


     public void connect() throws Exception {
        super.start();
    }

    public void sendValues(int type, float values[], long timestamp){
        try {
            out.writeInt(type);
            out.writeFloat(values[0]);
            out.writeFloat(values[1]);
            out.writeFloat(values[2]);
            out.writeLong(timestamp);
            out.flush();
        } catch(Exception e){
            Log.d("connector", "Error: " + e.getMessage() + " " + e.toString());
            return;
        }

        return;
    }


    @Override
    public void run() {
        try {
            socket = new Socket(server_addr, port);
            out = new DataOutputStream(socket.getOutputStream());
        } catch (Exception e){
            Log.d("Connector", "Error: " + e.getMessage());
            return;
        }

        while(true)
            try {
                sleep(1000, 0);
            } catch (Exception e){
                continue;
            }
    }
}
