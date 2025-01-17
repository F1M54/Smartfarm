import os
import time

def capture_photo():
    
    # Define the directory 
    save_directory = "/home/pc/images"
    
    # Create the directory if it doesn't exist
    if not os.path.exists(save_directory):
        os.makedirs(save_directory)
    
    # Create a unique filename
    file_name = os.path.join(save_directory, f"{time.strftime('%Y%m%d_%H%M%S')}.jpg")
  
    os.system(f"fswebcam -r 1280x720 --no-banner {file_name}")


while True:
    capture_photo()
    time.sleep(3600)  # Wait 1 hour
