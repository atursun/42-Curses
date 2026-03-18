import sys
import os

def main():
    # CGI standartlarında önce HTTP başlığı (header) ve boş bir satır yazdırılmalıdır
    print("Content-type: text/plain\n")
    # İstek metodunu kontrol edip POST verisini stdin'den okuyabilirsiniz
    method = os.environ.get("REQUEST_METHOD")
    if method == "POST":
        # POST ile gelen verinin boyutu CONTENT_LENGTH environment değişkeninde tutulur
        content_length_str = os.environ.get("CONTENT_LENGTH", "0")
        try:
            content_length = int(content_length_str)
            if content_length > 0:
                post_data = sys.stdin.read(content_length)
                print(f"Gelen POST Verisi: {post_data}")
        except ValueError:
            pass
    elif method == "GET":
        # GET parametreleri QUERY_STRING environment değişkeninde tutulur
        query_string = os.environ.get("QUERY_STRING", "")
        print(f"Gelen GET Verisi (Query String): {query_string}")

    sys.stdout.flush() # Eklenen satır: Çıktıları anında C++ sunucusuna gönder
    return 0

if __name__ == "__main__":
    main()