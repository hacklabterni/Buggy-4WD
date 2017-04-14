<?php
error_reporting(E_ALL); 
ini_set('display_errors', '1');

session_start();

define('SEM_KEY', 1000);

function noconcurrency() {
    $semRes = sem_get(SEM_KEY, 1, 0666, 0); // get the resource for the semaphore

    if(sem_acquire($semRes)) { // try to acquire the semaphore. this function will block until the sem will be available
        


//include "PhpSerial.php";
include "php_serial.class.php";

// $data = json_decode(file_get_contents('php://input'), true);
$data = file_get_contents('php://input');
//$data .= "\r\n";

$file = "/var/www/html/log.txt";
// Open the file to get existing content
// Write the contents to the file, 
// using the FILE_APPEND flag to append the content to the end of the file
// and the LOCK_EX flag to prevent anyone else writing to the file at the same time
file_put_contents($file, $data, FILE_APPEND | LOCK_EX);

$serial = unserialize($_SESSION["serial"]);
if ($serial == null)
{
$serial = new phpSerial;

$serial->deviceSet("/dev/ttyUSB0");
//$serial->confBaudRate(57600);
$serial->confBaudRate(9600);
//$serial->confBaudRate(38400);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);
$serial->confFlowControl("none");
 
// Then we need to open it
//$serial->deviceOpen('w+');
$serial->deviceOpen();
// To write into
sleep(2);

$_SESSION["serial"] = serialize($serial);

}


//$serial = new PhpSerial;
//$serial->sendMessage($data,1);
$serial->sendMessage("{\"x\":264,\"y\":11}");
sleep(1);
//$read = $serial->readPort(1024);
//file_put_contents($file, $read, FILE_APPEND | LOCK_EX);
//$serial->deviceClose();
//$serial->deviceOpen();
//sleep(1);
$serial->sendMessage("{\"x\":492,\"y\":249}");
sleep(1);
//$read = $serial->readPort(1024);
//file_put_contents($file, $read, FILE_APPEND | LOCK_EX);
//$serial->deviceClose();
//$serial->deviceOpen();
//sleep(1);
$serial->sendMessage("{\"x\":255,\"y\":509}");
sleep(1);
//$read = $serial->readPort(1024);
//file_put_contents($file, $read, FILE_APPEND | LOCK_EX);
//sleep(1);
//$serial->deviceClose();
//$serial->deviceOpen();
//sleep(1);
$serial->sendMessage("{\"x\":-1,\"y\":-1}");
sleep(1);
//$read = $serial->readPort(1024);
//file_put_contents($file, $read, FILE_APPEND | LOCK_EX);
// Or to read from
//$serial->flush();
//$read = $serial->readPort();
// If you want to change the configuration, the device must be closed
//$serial->deviceClose();

//file_put_contents($file, $read, FILE_APPEND | LOCK_EX);




        sem_release($semRes); // release the semaphore so other process can use it
    }
}

noconcurrency();

?>
