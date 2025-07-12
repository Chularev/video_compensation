1)	For convert input video to yuv420p format use next command  "ffmpeg -i Good_dog.mp4 -vf format=yuv420p -f rawvideo output.yuv"
2)	Get file info width and height "ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=s=x:p=0 Good_dog.mp4"
	
