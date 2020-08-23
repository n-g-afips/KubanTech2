package my.kubantech.rosseti;

import android.app.Activity;
import android.app.*;
import android.os.*;
import android.view.*;
import android.view.View.*;
import android.widget.*;
import android.content.*;
import android.content.res.*;
import android.graphics.*;
import android.graphics.drawable.*;
import android.media.*;
import android.net.*;
import android.text.*;
import android.text.style.*;
import android.util.*;
import android.webkit.*;
import android.animation.*;
import android.view.animation.*;
import java.util.*;
import java.util.regex.*;
import java.text.*;
import org.json.*;
import java.util.HashMap;
import java.util.ArrayList;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.TextView;
import android.media.SoundPool;
import java.util.Timer;
import java.util.TimerTask;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.DialogFragment;


public class HomeActivity extends  Activity { 
	
	private Timer _timer = new Timer();
	
	private HashMap<String, Object> aUnit = new HashMap<>();
	private String json = "";
	private double ni = 0;
	private double v = 0;
	private double a1 = 0;
	private double a2 = 0;
	private boolean fAlert = false;
	private boolean fDanger = false;
	private double warning = 0;
	private double danger = 0;
	private double stream = 0;
	private double nl = 0;
	
	private ArrayList<HashMap<String, Object>> lm_units = new ArrayList<>();
	private ArrayList<HashMap<String, Object>> lm_tmp = new ArrayList<>();
	
	private LinearLayout l_main;
	private LinearLayout l_top;
	private ListView lv_units;
	private TextView textview1;
	
	private SoundPool soundpool;
	private TimerTask delay;
	private RequestNetwork rn;
	private RequestNetwork.RequestListener _rn_request_listener;
	@Override
	protected void onCreate(Bundle _savedInstanceState) {
		super.onCreate(_savedInstanceState);
		setContentView(R.layout.home);
		initialize(_savedInstanceState);
		initializeLogic();
	}
	
	private void initialize(Bundle _savedInstanceState) {
		
		l_main = (LinearLayout) findViewById(R.id.l_main);
		l_top = (LinearLayout) findViewById(R.id.l_top);
		lv_units = (ListView) findViewById(R.id.lv_units);
		textview1 = (TextView) findViewById(R.id.textview1);
		rn = new RequestNetwork(this);
		
		_rn_request_listener = new RequestNetwork.RequestListener() {
			@Override
			public void onResponse(String _param1, String _param2, HashMap<String, Object> _param3) {
				final String _tag = _param1;
				final String _response = _param2;
				final HashMap<String, Object> _responseHeaders = _param3;
				if ("get".equals(_tag)) {
					lm_units.clear();
					lm_tmp = new Gson().fromJson(_response, new TypeToken<ArrayList<HashMap<String, Object>>>(){}.getType());
					nl = lm_tmp.size();
					for(int _repeat18 = 0; _repeat18 < (int)(lm_tmp.size()); _repeat18++) {
						nl--;
						aUnit = lm_tmp.get((int)nl);
						lm_units.add(aUnit);
					}
					_prepData(lm_units);
					lv_units.setAdapter(new Lv_unitsAdapter(lm_units));
					((BaseAdapter)lv_units.getAdapter()).notifyDataSetChanged();
				}
			}
			
			@Override
			public void onErrorResponse(String _param1, String _param2) {
				final String _tag = _param1;
				final String _message = _param2;
				
			}
		};
	}
	
	private void initializeLogic() {
		_initAudio();
		_iniitVallues();
		delay = new TimerTask() {
			@Override
			public void run() {
				runOnUiThread(new Runnable() {
					@Override
					public void run() {
						_prepData(lm_units);
						lv_units.setAdapter(new Lv_unitsAdapter(lm_units));
						((BaseAdapter)lv_units.getAdapter()).notifyDataSetChanged();
					}
				});
			}
		};
		_timer.schedule(delay, (int)(1000));
	}
	
	@Override
	protected void onActivityResult(int _requestCode, int _resultCode, Intent _data) {
		
		super.onActivityResult(_requestCode, _resultCode, _data);
		
		switch (_requestCode) {
			
			default:
			break;
		}
	}
	
	public void _iniitVallues () {
		lm_units.clear();
		if (false) {
			json = "[\n{\"name\":\"кип1\", \"value\":\"80\", \"alert1\":\"90\", \"alert2\":\"100\"},\n{\"name\":\"кип2\", \"value\":\"85\", \"alert1\":\"90\", \"alert2\":\"100\"},\n{\"name\":\"кип3\", \"value\":\"90\", \"alert1\":\"90\", \"alert2\":\"100\"},\n{\"name\":\"кип4\", \"value\":\"95\", \"alert1\":\"90\", \"alert2\":\"100\"},\n{\"name\":\"кип5\", \"value\":\"105\", \"alert1\":\"90\", \"alert2\":\"100\"}\n]";
			lm_units = new Gson().fromJson(json, new TypeToken<ArrayList<HashMap<String, Object>>>(){}.getType());
		}
		else {
			rn.startRequestNetwork(RequestNetworkController.GET, "http://virkato.h1n.ru?get=last", "get", _rn_request_listener);
		}
	}
	
	
	public void _prepData (final ArrayList<HashMap<String, Object>> _lm) {
		fAlert = false;
		fDanger = false;
		ni = _lm.size();
		for(int _repeat13 = 0; _repeat13 < (int)(_lm.size()); _repeat13++) {
			ni--;
			if (_lm.get((int)ni).containsKey("val") && (_lm.get((int)ni).containsKey("alert1") && _lm.get((int)ni).containsKey("alert2"))) {
				v = Double.parseDouble(_lm.get((int)ni).get("val").toString());
				a1 = Double.parseDouble(_lm.get((int)ni).get("alert1").toString());
				a2 = Double.parseDouble(_lm.get((int)ni).get("alert2").toString());
				if (v > a1) {
					_lm.get((int)ni).put("status", "1");
					fAlert = true;
				}
				if (v > a2) {
					_lm.get((int)ni).put("status", "2");
					fAlert = true;
					fDanger = true;
				}
			}
		}
		if (fAlert) {
			if (fDanger) {
				stream = soundpool.play((int)(danger), 1.0f, 1.0f, 1, (int)(0), 1.0f);
			}
			else {
				stream = soundpool.play((int)(warning), 1.0f, 1.0f, 1, (int)(0), 1.0f);
			}
		}
	}
	
	
	public void _gd (final View _view, final String _c, final String _sc, final double _r) {
		android.graphics.drawable.GradientDrawable gd = new android.graphics.drawable.GradientDrawable();
		
		gd.setColor(Color.parseColor(_c));
		gd.setCornerRadius((float)_r);
		gd.setStroke(2, Color.parseColor(_sc));
		
		_view.setBackground(gd);
	}
	
	
	public void _initAudio () {
		soundpool = new SoundPool((int)(1), AudioManager.STREAM_MUSIC, 0);
		warning = soundpool.load(getApplicationContext(), R.raw.beep, 1);
		danger = soundpool.load(getApplicationContext(), R.raw.crystal, 1);
	}
	
	
	public class Lv_unitsAdapter extends BaseAdapter {
		ArrayList<HashMap<String, Object>> _data;
		public Lv_unitsAdapter(ArrayList<HashMap<String, Object>> _arr) {
			_data = _arr;
		}
		
		@Override
		public int getCount() {
			return _data.size();
		}
		
		@Override
		public HashMap<String, Object> getItem(int _index) {
			return _data.get(_index);
		}
		
		@Override
		public long getItemId(int _index) {
			return _index;
		}
		@Override
		public View getView(final int _position, View _v, ViewGroup _container) {
			LayoutInflater _inflater = (LayoutInflater)getBaseContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			View _view = _v;
			if (_view == null) {
				_view = _inflater.inflate(R.layout.unit, null);
			}
			
			final LinearLayout linear1 = (LinearLayout) _view.findViewById(R.id.linear1);
			final LinearLayout l_unit = (LinearLayout) _view.findViewById(R.id.l_unit);
			final LinearLayout l_name = (LinearLayout) _view.findViewById(R.id.l_name);
			final LinearLayout l_value = (LinearLayout) _view.findViewById(R.id.l_value);
			final LinearLayout l_alert = (LinearLayout) _view.findViewById(R.id.l_alert);
			final TextView t_id = (TextView) _view.findViewById(R.id.t_id);
			final TextView t_date = (TextView) _view.findViewById(R.id.t_date);
			final TextView t_lab1 = (TextView) _view.findViewById(R.id.t_lab1);
			final TextView t_val1 = (TextView) _view.findViewById(R.id.t_val1);
			final TextView t_lab2 = (TextView) _view.findViewById(R.id.t_lab2);
			final TextView t_alert1 = (TextView) _view.findViewById(R.id.t_alert1);
			final TextView t_alert2 = (TextView) _view.findViewById(R.id.t_alert2);
			
			t_id.setText("Прибор");
			t_date.setText("Время");
			t_val1.setText("-");
			t_alert1.setText("-");
			t_alert2.setText("-");
			l_unit.setBackgroundColor(Color.TRANSPARENT);
			_gd(l_unit, "#FFffffff", "#ff000000", 8);
			_gd(t_alert1, "#ffffcc80", "#ff000000", 8);
			_gd(t_alert2, "#ffef9a9a", "#ff000000", 8);
			if (_data.size() > 0) {
				if (_data.get((int)_position).containsKey("status")) {
					if ("1".equals(_data.get((int)_position).get("status").toString())) {
						_gd(l_unit, "#ffffcc80", "#ff000000", 8);
					}
					if ("2".equals(_data.get((int)_position).get("status").toString())) {
						_gd(l_unit, "#ffef9a9a", "#ff000000", 8);
					}
				}
				if (_data.get((int)_position).containsKey("kip")) {
					t_id.setText(_data.get((int)_position).get("kip").toString());
				}
				if (_data.get((int)_position).containsKey("val")) {
					t_val1.setText(_data.get((int)_position).get("val").toString());
				}
				if (_data.get((int)_position).containsKey("dat")) {
					t_date.setText(_data.get((int)_position).get("dat").toString());
				}
				if (_data.get((int)_position).containsKey("alert1")) {
					t_alert1.setText(_data.get((int)_position).get("alert1").toString());
				}
				if (_data.get((int)_position).containsKey("alert2")) {
					t_alert2.setText(_data.get((int)_position).get("alert2").toString());
				}
			}
			
			return _view;
		}
	}
	
	@Deprecated
	public void showMessage(String _s) {
		Toast.makeText(getApplicationContext(), _s, Toast.LENGTH_SHORT).show();
	}
	
	@Deprecated
	public int getLocationX(View _v) {
		int _location[] = new int[2];
		_v.getLocationInWindow(_location);
		return _location[0];
	}
	
	@Deprecated
	public int getLocationY(View _v) {
		int _location[] = new int[2];
		_v.getLocationInWindow(_location);
		return _location[1];
	}
	
	@Deprecated
	public int getRandom(int _min, int _max) {
		Random random = new Random();
		return random.nextInt(_max - _min + 1) + _min;
	}
	
	@Deprecated
	public ArrayList<Double> getCheckedItemPositionsToArray(ListView _list) {
		ArrayList<Double> _result = new ArrayList<Double>();
		SparseBooleanArray _arr = _list.getCheckedItemPositions();
		for (int _iIdx = 0; _iIdx < _arr.size(); _iIdx++) {
			if (_arr.valueAt(_iIdx))
			_result.add((double)_arr.keyAt(_iIdx));
		}
		return _result;
	}
	
	@Deprecated
	public float getDip(int _input){
		return TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, _input, getResources().getDisplayMetrics());
	}
	
	@Deprecated
	public int getDisplayWidthPixels(){
		return getResources().getDisplayMetrics().widthPixels;
	}
	
	@Deprecated
	public int getDisplayHeightPixels(){
		return getResources().getDisplayMetrics().heightPixels;
	}
	
}
