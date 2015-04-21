GolgiLib.init();
GolgiNet.init();
GA1.ServiceInit();
GolgiNet.setCredentials(Golgi_DEVKEY, Golgi_APPKEY, "Browser");

var gto = {};
gto["EXPIRY"] = 60;
var onOff = 0;
var portrait = 0;

function adjustSize(){
    var winW = 640;
    var winH = 480;
    if (document.body && document.body.offsetWidth) {
        winW = document.body.offsetWidth;
        winH = document.body.offsetHeight;
    }
    if (document.compatMode=='CSS1Compat' &&
    document.documentElement &&
        document.documentElement.offsetWidth ) {
        winW = document.documentElement.offsetWidth;
        winH = document.documentElement.offsetHeight;
    }
    if (window.innerWidth && window.innerHeight) {
        winW = window.innerWidth;
        winH = window.innerHeight;
    }
    console.log("Window: " + winW + "x" + winH);
    if(winW < winH){
        if(portrait == 0){
            portrait = 1;
            console.log("Switch to portrait");
            document.getElementById("bulbdiv").style.height="50%";
        }
    }
    else{
        if(portrait != 0){
            portrait = 0;
            console.log("Switch to landscape");
            document.getElementById("bulbdiv").style.height="100%";
        }
    }
}

function ledControl(state){
    GA1.GA1Svc.setLED({
        success : function(){
                console.log("setLED: success(1)");

                if(onOff == 0){
                    document.getElementById("bulbimg").src="bulb-off.jpg";    
                }
                else{
                    document.getElementById("bulbimg").src="bulb-on.jpg";    
                }
                document.getElementById("shader").style.zIndex=-1;
            },
         failWithGolgiException : function(golgiException){
                document.getElementById("shader").style.zIndex=-1;
                console.log("startGame: failed: '" + golgiException.getErrText() + "'/ " + golgiException.getErrType());
            }
        },
        "HW",
        gto,
        state);
}


function ledToggle(){
    onOff = onOff ^ 1;
    adjustSize();
    document.getElementById("shader").style.zIndex=3;
    ledControl(onOff);
}


GolgiNet.register(function(err){
        if(err != undefined){
            console.log("Failed to register");
        }
        else{
            console.log("Register OK");
        }
        adjustSize();
    });


