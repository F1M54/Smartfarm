import os
import time
from datetime import datetime
import threading

def capture_photo():
    
    save_directory = "/home/pc/images"
    if not os.path.exists(save_directory):
        os.makedirs(save_directory)
    file_name = os.path.join(save_directory, f"{datetime.now().strftime('%Y%m%d_%H%M%S')}.jpg")
    os.system(f"fswebcam -r 1280x720 --no-banner {file_name}")
    return file_name

def hourly_capture():
    
    while True:
        capture_photo()
        time.sleep(3600)

def serve_new_photo_request():
   
    request_file = "/home/pc/request_capture.txt"
    while True:
        if os.path.exists(request_file):
            capture_photo()
            os.remove(request_file)
        time.sleep(1)


thread1 = threading.Thread(target=hourly_capture)
thread2 = threading.Thread(target=serve_new_photo_request)

thread1.start()
thread2.start()
