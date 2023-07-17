#include "mongoose.h"

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        // Enviar la respuesta HTTP con el contenido HTML
        const char* html = "<!DOCTYPE html>\n"
                           "<html>\n"
                           "<head>\n"
                           "    <title>Gráfico de barras</title>\n"
                           "    <script src=\"chart.js\"></script>\n"
                           "</head>\n"
                           "<body>\n"
                           "    <canvas id=\"myChart\"></canvas>\n"
                           "    <script>\n"
                           "        // Código JavaScript para crear el gráfico\n"
                           "        var ctx = document.getElementById('myChart').getContext('2d');\n"
                           "        var chart = new Chart(ctx, {\n"
                           "            type: 'bar',\n"
                           "            data: {\n"
                           "                labels: ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo'],\n"
                           "                datasets: [{\n"
                           "                    label: 'Ventas',\n"
                           "                    data: [120, 250, 180, 300, 200],\n"
                           "                    backgroundColor: 'rgba(75, 192, 192, 0.6)'\n"
                           "                }]\n"
                           "            },\n"
                           "            options: {\n"
                           "                scales: {\n"
                           "                    y: {\n"
                           "                        beginAtZero: true\n"
                           "                    }\n"
                           "                }\n"
                           "            }\n"
                           "        });\n"
                           "    </script>\n"
                           "</body>\n"
                           "</html>";

        mg_printf(nc, "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html\r\n"
                      "Content-Length: %d\r\n"
                      "\r\n"
                      "%s", (int) strlen(html), html);

       // nc->fd |= mg_fs_close;
    }
}

int main() {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr);

    if((nc = mg_http_listen(&mgr, "8080", ev_handler,&mgr)) == NULL)
     //MG_ERROR(("Cannot listen on %s. Use http://ADDR:PORT or :PORT", s_listening_address));
        return 1;

    printf("Servidor web en ejecución en http://localhost:8080\n");

    while (1) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}