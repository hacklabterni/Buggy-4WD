<?php

//$localIP = getHostByName(getHostName());
$localIP = $_SERVER['HTTP_HOST'];
?>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
<html>
 <head>
  <title>PHP Test</title>
 </head>
 <body>
 <!--?php echo '<p>Hello World</p>'; ?--> 

 <table width="100%" height="100%">
   <tr>
     <td><iframe src="http://<?php echo $localIP?>:8081/" width="640px" height="480px"></iframe></td>
     <td><div id="quadrants" style="background-image: url(img/quadrants.png); height: 511px; width: 511px; border: 1px solid black;"> </div> </td>
   </tr>
   <tr>
     <td colspawn="2"><div id="log"></div></td>
   </tr>

 </table>
 <script type="text/javascript" src="/js/HLT_Buggy4WD.js"></script>
 <script>
 
   $(function(){
   
   HLT_Buggy4WD.init();

   var mousePressed = false;
   var quadrants = $("#quadrants");
   var log = $("#log");
   log.append( "<div>test</div>" );
   
   quadrants.mousedown(function(e){
      if (e.which==1) {
       var offset = $(this).offset();
       sendPoint((e.pageX - offset.left), (e.pageY - offset.top));
     }
    });

   quadrants.mouseup(function(e){      
       sendPoint(-1, -1);
    });

   quadrants.mouseout(function(e){
       sendPoint(-1, -1);
    }); 

   quadrants.mousemove(function(e){
     if (e.which==1) {
       var offset = $(this).offset();
       sendPoint((e.pageX - offset.left), (e.pageY - offset.top));       
     }
    });

   function sendPoint(x,y){

     var data = '{"x":'+Math.trunc(x)+',"y":'+Math.trunc(y)+'}'; 
     var msg = "Handler for .mousemove() called at "+data;
     log.text(msg);

	 HLT_Buggy4WD.getUtils().sendCommand({
							request: data,
							callback: function(resp) {								
								if(resp) {
									alert(resp);
								}
							},
							onerror: function(err) {
								if(err) {
									alert(err);
								}
							}
						});
	};

   });   
</script>

 </body>
</html>



