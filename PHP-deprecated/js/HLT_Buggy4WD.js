/*
 * 
 * 
 * 
 * 
 * START HLT_Buggy4WD
 * 
 * 
 * 
 * 
 * 
 */

window.HLT_Buggy4WD = new function() {

	this.sendCommandPath = "/sendCommand.php";	
	
	this.init = function(params) {		
		this.currentUtils = new this._utils();
	};
	
	this.getUtils = function() {
		return this.currentUtils;
	};
	
	this._utils = function() {
		this.sendCommand = function(params) {
			if(!params || !params.request ) {
				throw new Error('Errore nei parametri');
			} 	
			   
			HLT_Buggy4WD._sendRequest({ path: HLT_Buggy4WD.sendCommandPath, 
								  method: 'POST', 
								  postData: params.request, 
								  callback: params.callback, 
								  onerror: params.onerror,
								  onnetworkerror: params.onnetworkerror});
		};		
	};
	
	this._sendRequest = function(params) {
		if(!params) params = {};
		var path = params.path || '';
		var method = params.method || (params.postData ? 'POST' : 'GET');
		var postData = params.postData;
		var callback = params.callback || function() {};
		var onerror = params.onerror || function() {};
		var onnetworkerror = params.onnetworkerror || function() {};
		
		var _this = this;
	    var req = this._createXMLHTTPObject();
	    if (!req) return;
	    var url = this._getContextPath() + path;
	    req.open(method,url,true);
	    if (postData) {
	        req.setRequestHeader('Content-type','application/json; charset=utf-8');
	    }
	    req.onreadystatechange = function () {
	        if (req.readyState != 4) return;
	        if (req.status != 200 && req.status != 304) {
	        	console.error(req);
	        	if(onerror) {	        		
	        		var ret = HLT_Buggy4WD._parseResponse(req);
					onerror(ret, req);
	        	}
	        } else {        		
	        	if(callback) {
	        		var ret = HLT_Buggy4WD._parseResponse(req);
        		    callback(ret, req);
	        	}
	        }
	    };
	    
	    req.onerror = function () {
	    	if(onnetworkerror) {
	    		onnetworkerror("Errore connessione al servizio");
	    	}
	    };
	    
	    if (req.readyState == 4) return;
	    req.send(postData);
	};
	
	this._parseResponse = function(req) {
		var ret = null;
		var ct = req.getResponseHeader('content-type')
		if(ct && ct.lastIndexOf('application/json', 0) === 0) {
			try {
				ret = JSONNoConflicts.parse(req.responseText);
			} catch(e) {
				console.error(e);
			}
		}
		return ret;
	};
	
	this._XMLHttpFactories = [
	    function () {return new XMLHttpRequest()},
	    function () {return new ActiveXObject("Msxml2.XMLHTTP")},
	    function () {return new ActiveXObject("Msxml3.XMLHTTP")},
	    function () {return new ActiveXObject("Microsoft.XMLHTTP")}
	];
	
	this._createXMLHTTPObject = function() {
	    var xmlhttp = false;
	    for (var i=0;i<this._XMLHttpFactories.length;i++) {
	        try {
	            xmlhttp = this._XMLHttpFactories[i]();
	        }
	        catch (e) {
	            continue;
	        }
	        break;
	    }
	    return xmlhttp;
	};
	
	this._getContextPath = function() {
		   return window.location.pathname.substring(0, window.location.pathname.indexOf("/",2));
	};
}