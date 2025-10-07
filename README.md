**!! ARCHIVED BY EVAN TONE ON 10/7/2025 !!**

# To enable live streaming on boot up check if the stream service file exists:
cat /etc/systemd/system/youtube-stream.service


# Ensure that User=POS and the path matches your username and script location. If not the stream service file needs to be modified.


# Enable stream on boot:
sudo systemctl enable youtube-stream.service


# Check status
sudo systemctl status youtube-stream.service


# Watch live logging
journalctl -u youtube-stream.service -f




# Tempo. Stop the stream
sudo systemctl stop youtube-stream.service


# Restart it
sudo systemctl start youtube-stream.service


# Disable from auto start on booting
sudo systemctl disable youtube-stream.service


# Re-enable on boot
sudo systemctl enable youtube-stream.service


# Editing the stream file
sudo nano ~/youtube-stream.sh


# IF the stream shell is edited then one has to ensure the service file is ALSO restarted with the new version
sudo systemctl restart youtube-stream.service




# WIFI update part 2 in terminal (copy of whats above, but this is easier to copy and paste :) )
sudo nmcli dev wifi list
sudo nmcli device wifi connect "Jacob’s iPhone (6)" password "zachzach"
