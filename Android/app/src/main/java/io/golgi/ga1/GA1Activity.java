package io.golgi.ga1;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;

import com.openmindnetworks.golgi.api.GolgiAPI;
import com.openmindnetworks.golgi.api.GolgiAPIHandler;
import com.openmindnetworks.golgi.api.GolgiException;

import io.golgi.apiimpl.android.GolgiService;
import io.golgi.ga1.gen.GA1Service;
import io.golgi.ga1.gen.GolgiKeys;


public class GA1Activity extends ActionBarActivity {

    private boolean bulbOn = false;
    private ImageButton ib;

    public static void DBG(String str){
        Log.i("GA1", str);
    }



    public void register() {
        GolgiAPI.getInstance().register(
                GolgiKeys.DEV_KEY,
                GolgiKeys.APP_KEY,
                "Android",
                new GolgiAPIHandler() {
                    @Override
                    public void registerSuccess() {
                        DBG("Golgi registration Success");
                        if(ib != null) {
                            ib.post(new Runnable() {
                                @Override
                                public void run() {
                                    ib.setEnabled(true);
                                    ib.setAlpha(1.0f);
                                }
                            });
                        }
                    }

                    @Override
                    public void registerFailure() {
                        DBG("Golgi registration Failure");
                    }
                });
        DBG("Register called");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ga1);
        GolgiService.runInForeground(this);
        register();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_ga1, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }



    @Override
    public void onResume() {
        super.onResume();
        ib = (ImageButton)findViewById(R.id.imageButton);

        ib.setImageResource(bulbOn ? R.drawable.bulb_on : R.drawable.bulb_off);
        ib.setEnabled(false);
        ib.setAlpha(0.5f);

        register();

        GolgiAPI.usePersistentConnection();


        ib.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DBG("Send setLED");
                ib.setEnabled(false);
                ib.setAlpha(0.5f);
                GA1Service.setLED.sendTo(new GA1Service.setLED.ResultReceiver() {
                    @Override
                    public void failure(GolgiException ex) {
                        DBG("Failed: " + ex.getErrText());
                    }

                    @Override
                    public void success() {
                        DBG("Success");
                        bulbOn = !bulbOn;
                        ib.post(new Runnable() {
                            @Override
                            public void run() {
                                ib.setImageResource(bulbOn ? R.drawable.bulb_on : R.drawable.bulb_off);
                                ib.setEnabled(true);
                                ib.setAlpha(1.0f);
                            }
                        });
                    }
                }, "HW", (bulbOn ? 0 : 1));
                DBG("Clicked");
            }
        });

    }

    @Override
    public void onPause() {
        super.onPause();
        GolgiAPI.useEphemeralConnection();
    }


}
