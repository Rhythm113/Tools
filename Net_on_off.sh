#©Infinity Creators All Rights Received
#Licenced Under Open GNU 
#Any kind of Modification of Main Code or Copying without permission is prohibited by Copyright Rights
#Currently Support ROOT Only
#Code By : @Rhytym113

#--------------------------------User Section-------------------------------#
#Edit The Value Here as Your Wish
#Configaration
TIME="4" #Time interval For Data On Off (In seconds) 
DELAY="3" #Delay (How much time Should The Data Remains Off ) [ in Seconds]
#End of Configuration

##------------------------------------##

#Main Code
#DON'T MODIFY THIS !
echo " Auto Data On Off Shell Script"
echo " Author : @Rhythm113"
echo "© Infinity Creators"
echo "Console : "
echo "Starting.."
echo "Settings : Time. : $TIME s , Delay : $DELAY s"
sleep 2
echo "Data Will be Turned Off After $TIME seconds.."
while true
do
sleep $TIME
GW="$(su -c /sbin/route -n | awk '$1=="0.0.0.0" {print $2; exit}')"
su -c /sbin/route del default gw "$GW"
echo "$GW" >> /sdcard/local.txt
echo "Data Turned Off"
sleep $DELAY
su -c /sbin/route add default gw "$(cat /sdcard/local.txt)"
echo "Data Turned On"
done
#Author : @Rhythm113
