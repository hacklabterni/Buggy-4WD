<?php

error_reporting(E_ALL); ini_set('display_errors', '1');

include "PhpSerial.php";

// $data = json_decode(file_get_contents('php://input'), true);
$data = file_get_contents('php://input');

$file = "/var/www/html/log.txt";
// Open the file to get existing content
// Write the contents to the file, 
// using the FILE_APPEND flag to append the content to the end of the file
// and the LOCK_EX flag to prevent anyone else writing to the file at the same time
file_put_contents($file, $data, FILE_APPEND | LOCK_EX);



$serial = new PhpSerial;
$serial->deviceSet("/dev/ttyUSB0");
$serial->confBaudRate(57600);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);
$serial->confFlowControl("none");
 
// Then we need to open it
$serial->deviceOpen('w+');
// To write into
$serial->sendMessage($data);
// Or to read from
$read = $serial->readPort();
// If you want to change the configuration, the device must be closed
$serial->deviceClose();

file_put_contents($file, $read, FILE_APPEND | LOCK_EX);


?>
