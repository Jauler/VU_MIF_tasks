package jauler.sensormouse;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class Startup extends Activity implements SensorEventListener {
    Button connect;
    SensorManager sm;
    Sensor gyroSens, accelSens;
    Boolean connected = false;
    Connector c;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_startup);
        connect = (Button)findViewById(R.id.connectButton);
        connect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Integer port;
                try {
                    String addr = ((EditText) findViewById(R.id.serverAddr)).getText().toString();
                    if(addr.length() <= 0) {
                        throw new IllegalArgumentException("Invalid server address");
                    }
                    try {
                        port = Integer.parseInt(((EditText) findViewById(R.id.port)).getText().toString());
                    }catch(Exception e) {
                        throw new IllegalArgumentException("Invalid port number");
                    }

                    c = new Connector(addr, port);
                    c.connect();
                } catch (Exception e){
                    Log.e("OnClock", "Error: " + e.getMessage());
                    Toast.makeText(getApplicationContext(), "Connection Failed", Toast.LENGTH_SHORT);
                    return;
                }

                Toast.makeText(getApplicationContext(), "Connection Successful", Toast.LENGTH_SHORT);

                try {
                    Thread.sleep(1000, 0);
                } catch(Exception e){}
                connected = true;
            }
        });
        return;
    }


    @Override
    public void onSensorChanged(SensorEvent e){
        if(!connected)
            return;

        try {
            if (e.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                c.sendValues(0, e.values, e.timestamp);
            } else if (e.sensor.getType() == Sensor.TYPE_GYROSCOPE) {
                c.sendValues(1, e.values, e.timestamp);
            }
        } catch(Exception exception){
            Log.d("OnSensorChanged", "Error: " + exception.getMessage() + " " + exception.toString());
            connected = false;
            return;
        }

        return;
    }

    @Override
    public void onAccuracyChanged(Sensor s, int accuracy) {
        return;
    }

    @Override
    protected void onResume(){
        super.onResume();
        sm = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        gyroSens = sm.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        if(gyroSens == null)
            return;
        accelSens = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        if(accelSens == null)
            return;

        sm.registerListener(this, gyroSens, SensorManager.SENSOR_DELAY_UI);
        sm.registerListener(this, accelSens, SensorManager.SENSOR_DELAY_UI);

    }

    @Override
    protected void onPause(){
        super.onPause();
        sm.unregisterListener(this);
    }
}
