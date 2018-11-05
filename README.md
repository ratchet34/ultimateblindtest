# ultimateblindtest

Euh Yo!

Le format des paquets TCP pour balancer des réponses c'est "username|artist|songname|heardin".

Tu peux laisser vide si t'as pas de réponse genre "ratchet|||Mario Kart"

Attention l'algo supposé être gentil avec la casse et les fautes de frappe est pas encore au point...
Mais genre pas du tout.

En bonus, le script php pour balancer des réponses (ouais c'est dégueux je sais) :

<?php
if (isset($_POST['artist'])) {
ini_set('display_errors', true); error_reporting(E_ALL); // <- for debugging purposes only

$socket=socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ( !$socket ) {
    $errno = socket_last_error();
    $error = sprintf('%s (%d)', socket_strerror($errno), $errno);
    trigger_error($error, E_USER_ERROR);
}

if ( !socket_connect($socket, '127.0.0.1', 50885) ) {
    $errno = socket_last_error($socket);
    $error = sprintf('%s (%d)', socket_strerror($errno), $errno);
    trigger_error($error, E_USER_ERROR);
}

$buff=$_POST['user']."|".$_POST['artist']."|".$_POST['name']."|".$_POST['heard'];
$length = strlen($buff);
$sent = socket_write($socket, $buff, $length);
if ( FALSE===$sent ) {
    $errno = socket_last_error($socket);
    $error = sprintf('%s (%d)', socket_strerror($errno), $errno);
    trigger_error($error, E_USER_ERROR);
}
else if ( $length!==$sent ) {
    $msg = sprintf('only %d of %d bytes sent', $length, $sent);
    trigger_error($msg, E_USER_NOTICE);
}
else {
    echo $sent.' sent';
}
socket_close($socket);
}
if (isset($_POST['user'])) {

?>

<form method="POST" action="#">
    <input type="text" name="artist" placeholder="artist" />
    <input type="text" name="name" placeholder="song name" />
    <input type="text" name="heard" placeholder="heard in" />
    <input type="hidden" name="user" value="<?php echo $_POST['user']; ?>" />
    <input type="submit"/>
</form>

<?php

}
else {

?>

<form method="POST" action="#">
    <input type="text" name="user" placeholder="Username" />
</form>
<?php
}
?>
