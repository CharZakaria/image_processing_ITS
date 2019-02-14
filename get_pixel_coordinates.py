import cv2

# mouse callback function
	def set_ground_truth(event,x,y,flags,param):
	    if event == cv2.EVENT_LBUTTONDBLCLK:
	        pt_src = (x,y)
	        print(pt_src)
	
	        cv2.circle(frame,(x,y),5,(255,0,0),-1)

	
	cv2.namedWindow('image', cv2.WINDOW_NORMAL)
	cv2.setMouseCallback('image',set_ground_truth)

	while(1):
	    cv2.imshow('image',frame)
	    if cv2.waitKey(20) & 0xFF == 27:
	        break
	cv2.destroyAllWindows()
