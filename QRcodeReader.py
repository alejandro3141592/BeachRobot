import cv2


def read_qr_code(frame):
    ret_qr = None

    mirrored_image = cv2.flip(frame, 1)
    print("a")
    detect = cv2.QRCodeDetector()
    retval, decoded_info, points, straight_qrcode = detect.detectAndDecodeMulti(mirrored_image)
    print(retval)
    print(decoded_info)
        
            
    return decoded_info
def read_qr_code():
    # Initialize camera
    cap = cv2.VideoCapture(0)

    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Decode QR code
        detect = cv2.QRCodeDetector()

        ## SI POR ALGUN MOTIVO NO FUNCIONA EL CODIGO, DESCOMENTAR LA LINEA DE ABAJO, Y EN LUGAR DE FRAME PASAR MIRRORED_FRAME A LA PROXIMA FUNCION
        #mirrored_image = cv2.flip(frame, 1)

        # Draw rectangle and text around QR code
        retval, decoded_info, points, straight_qrcode = detect.detectAndDecodeMulti(frame)

        print(decoded_info)
        cv2.imshow('frame', frame)

            # Wait for 'q' key to exit
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the camera and close the window
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    read_qr_code()
