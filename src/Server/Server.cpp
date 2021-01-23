#include "Server.h"

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QBoxLayout>

#include <QWebSocket>
#include <QWebSocketServer>
#include <QCoreApplication>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#define WINDOWHEIGHT			600
#define WINDOWWIDTH				800

#define DEFAULT_PORT			1234

Server::Server(QWidget *parent)
	: QWidget(parent)
{
	this->resize(QSize(WINDOWWIDTH, WINDOWHEIGHT));
	this->setUI();
}

void Server::setUI()
{
	QButtonGroup * button_group = new QButtonGroup;
	button_group->setExclusive(true);

	// layout1
	QLabel * server_info_Label = new QLabel("server information");
	default_port_Button = new QPushButton("default");
	default_port_Button->setFixedWidth(WINDOWWIDTH / 8);

	QHBoxLayout *  server_Layout_1 = new QHBoxLayout;
	server_Layout_1->addWidget(server_info_Label);
	server_Layout_1->addWidget(default_port_Button);

	// layout2
	QLabel * ip_Label = new QLabel("url");
	ip_Label->setFixedWidth(WINDOWWIDTH / 16);
	ip_Label->setFixedHeight(WINDOWHEIGHT / 20);
	ip_Label->setAlignment(Qt::AlignCenter);
	ip_LineEdit = new QLineEdit;
	ip_LineEdit->setFixedWidth(4 * WINDOWWIDTH / 16);
	ip_LineEdit->setFixedHeight(WINDOWHEIGHT / 20);
	QLabel * port_Label = new QLabel("port");
	port_Label->setFixedWidth(WINDOWWIDTH / 16);
	port_Label->setFixedHeight(WINDOWHEIGHT / 20);
	port_Label->setAlignment(Qt::AlignCenter);
	port_SpinBox = new QSpinBox;
	port_SpinBox->setRange(0, 65535);
	port_SpinBox->setFixedWidth(WINDOWWIDTH / 8);
	port_SpinBox->setFixedHeight(WINDOWHEIGHT / 20);
	start_server_Button = new QPushButton("start server");
	stop_server_Button = new QPushButton("finish server");
	start_server_Button->setFixedWidth(WINDOWWIDTH / 6);
	stop_server_Button->setFixedWidth(WINDOWWIDTH / 6);
	start_server_Button->setFixedHeight(WINDOWHEIGHT / 16);
	stop_server_Button->setFixedHeight(WINDOWHEIGHT / 16);

	start_server_Button->setCheckable(true);
	stop_server_Button->setCheckable(true);
	button_group->addButton(start_server_Button, 0);
	button_group->addButton(stop_server_Button, 1);

	QHBoxLayout * server_Layout_2 = new QHBoxLayout;
	server_Layout_2->addWidget(ip_Label);
	server_Layout_2->addWidget(ip_LineEdit);
	server_Layout_2->addWidget(port_Label);
	server_Layout_2->addWidget(port_SpinBox);
	server_Layout_2->addWidget(start_server_Button);
	server_Layout_2->addWidget(stop_server_Button);

	// Layout3
	QLabel * online_client_Label = new QLabel("online client");
	QHBoxLayout * server_Layout_3 = new QHBoxLayout;
	server_Layout_3->addWidget(online_client_Label);

	// Layout4
	client1_Button = new QPushButton("clientA");
	client2_Button = new QPushButton("clientB");
	client3_Button = new QPushButton("clientC");
	client4_Button = new QPushButton("clientD");

	client1_Button->setVisible(false);
	client2_Button->setVisible(false);
	client3_Button->setVisible(false);
	client4_Button->setVisible(false);

	client1_Button->setFixedWidth(WINDOWWIDTH / 6);
	client2_Button->setFixedWidth(WINDOWWIDTH / 6);
	client3_Button->setFixedWidth(WINDOWWIDTH / 6);
	client4_Button->setFixedWidth(WINDOWWIDTH / 6);
	client1_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client2_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client3_Button->setFixedHeight(WINDOWHEIGHT / 16);
	client4_Button->setFixedHeight(WINDOWHEIGHT / 16);

	QHBoxLayout * server_Layout_4 = new QHBoxLayout;
	server_Layout_4->addWidget(client1_Button);
	server_Layout_4->addWidget(client2_Button);
	server_Layout_4->addWidget(client3_Button);
	server_Layout_4->addWidget(client4_Button);

	// Layout5
	QLabel * receive_message_Label = new QLabel("message from client");
	QHBoxLayout * server_Layout_5 = new QHBoxLayout;
	server_Layout_5->addWidget(receive_message_Label);

	// Layout6
	receive_client_message_TextEdit = new QTextEdit;
	receive_client_message_TextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // set the Vertical ScrollBar
	receive_client_message_TextEdit->setReadOnly(true);
	receive_client_message_TextEdit->setFixedHeight(WINDOWHEIGHT / 2);
	QHBoxLayout * server_Layout_6 = new QHBoxLayout;
	server_Layout_6->addWidget(receive_client_message_TextEdit);

	// Layout7
	QPushButton * clear_Button = new QPushButton("clear");
	clear_Button->setFixedWidth(WINDOWWIDTH / 8);
	clear_Button->setFixedHeight(WINDOWHEIGHT / 16);
	QLabel * empty_Label = new QLabel();
	empty_Label->setFixedWidth(5 * WINDOWWIDTH / 8);
	empty_Label->setFixedHeight(WINDOWHEIGHT / 16);
	QLabel * log_write_Label = new QLabel("Log Write");
	log_write_Label->setFixedWidth(WINDOWWIDTH / 8);
	log_write_Label->setFixedHeight(WINDOWHEIGHT / 16);
	log_write_Label->setAlignment(Qt::AlignCenter);
	log_write_Radiobutton = new QRadioButton();
	log_write_Radiobutton->setChecked(true);
	log_write_Radiobutton->setFixedSize(QSize(WINDOWWIDTH / 8, WINDOWHEIGHT / 16));

	QHBoxLayout * server_Layout_7 = new QHBoxLayout;
	server_Layout_7->addWidget(clear_Button);
	server_Layout_7->addWidget(empty_Label);
	server_Layout_7->addWidget(log_write_Label);
	server_Layout_7->addWidget(log_write_Radiobutton);

	// VLayout
	QVBoxLayout * server_Layout = new QVBoxLayout;
	server_Layout->addLayout(server_Layout_1, 0.5);
	server_Layout->addLayout(server_Layout_2, 2);
	server_Layout->addLayout(server_Layout_3, 0.5);
	server_Layout->addLayout(server_Layout_4, 2);
	server_Layout->addLayout(server_Layout_5, 0.5);
	server_Layout->addLayout(server_Layout_6, 4);
	server_Layout->addLayout(server_Layout_7, 1);

	setLayout(server_Layout);
	this->setWindowTitle("Websocket Server");
	
	// initialize variable
	server_socket = new QWebSocketServer("server", QWebSocketServer::NonSecureMode);
	current_date_time = new QDateTime();
	log_write_state = true;
	current_client_num = 0;

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		clients_state[i] = 0;
	}
	
	ip_LineEdit->setEnabled(false);
	stop_server_Button->setEnabled(false);

	// create dir to save log and chat message history
	QString path = QCoreApplication::applicationDirPath();
	QDir * log_Dir = new QDir;
	log_Dir_path = QString("%1/log").arg(path);
	if (!log_Dir->exists(log_Dir_path))
	{
		if (log_Dir->mkdir(log_Dir_path))
		{
			this->receive_message("log dir create successfully!");
		}
		else
		{
			this->receive_message("log dir create failed!");
		}
	}
	else
	{
		this->receive_message("log dir exist!");
	}

	QDir * base_Dir = new QDir;
	QString base_Dir_path = QString("%1/chat record").arg(path);
	base_Dir->mkdir(base_Dir_path);

	QDir * chat_record_Dir = new QDir;
	chat_record_Dir_path = QString("%1/server").arg(base_Dir_path);
	if (!chat_record_Dir->exists(chat_record_Dir_path))
	{
		if (chat_record_Dir->mkdir(chat_record_Dir_path))
		{
			this->receive_message("chat record dir create successfully!");
		}
		else
		{
			this->receive_message("chat record dir create failed!");
		}
	}
	else
	{
		this->receive_message("chat record dir exist!");
	}

	//// connect button / line / Text Edit ////

	connect(default_port_Button, &QPushButton::clicked, this, &Server::set_default_port);
	connect(start_server_Button, &QPushButton::clicked, this, &Server::start_server);
	connect(stop_server_Button, &QPushButton::clicked, this, &Server::stop_server);
	connect(clear_Button, &QPushButton::clicked, this, &Server::clear_message_record);

	connect(server_socket, SIGNAL(newConnection()), this, SLOT(new_connection()));

	// log write
	connect(log_write_Radiobutton, &QPushButton::clicked, this, &Server::log_write_state_change);
}

void Server::set_default_port()
{
	port_SpinBox->setValue(DEFAULT_PORT);
}

void Server::start_server()
{
	int port = port_SpinBox->text().toInt();
	server_socket->listen(QHostAddress::Any, port);
	QString server_url = server_socket->serverUrl().toString();

	ip_LineEdit->setText(server_url);
	ip_LineEdit->setEnabled(true);
	ip_LineEdit->setReadOnly(true);
	port_SpinBox->setEnabled(false);
	default_port_Button->setEnabled(false);
	start_server_Button->setEnabled(false);
	stop_server_Button->setEnabled(true);

	QString msg = "start server!";
	this->receive_message(msg);
}

void Server::stop_server()
{
	server_socket->close();
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (clients_state[i] == 1)
		{
			clients[i]->close();
		}
		clients_state[i] = 0;	
	}

	ip_LineEdit->clear();
	ip_LineEdit->setEnabled(false);
	port_SpinBox->setEnabled(true);
	default_port_Button->setEnabled(true);
	start_server_Button->setEnabled(true);
	stop_server_Button->setEnabled(false);

	QString msg = "stop server!";
	this->receive_message(msg);
}

void Server::new_connection()
{
	if (current_client_num < MAX_CLIENT)
	{
		client_socket = server_socket->nextPendingConnection();
		connect(client_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(receive_client_message(QString)));
		connect(client_socket, SIGNAL(disconnected()), this, SLOT(client_disconnect()));

		QString send_message;
		QString tips_message;
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (clients_state[i] == 0)
			{
				clients[i] = client_socket;
				send_message = QString("You are the client %1").arg(i + 1);
				tips_message = QString("there is a new connection!\n clinet %1 is online!").arg(i + 1);
				client_socket->sendTextMessage(send_message);
				this->transmit_store_message(i + 1);

				switch (i)
				{
					case 0: client1_Button->setVisible(true);
							break;
					case 1: client2_Button->setVisible(true);
						    break;
					case 2: client3_Button->setVisible(true);
						    break;
					case 3: client4_Button->setVisible(true);
							break;
				}
				clients_state[i] = 1;
				break;
			}
		}
		current_client_num++;
		this->receive_message(tips_message);
	}	
}

void Server::client_disconnect()
{
	QWebSocket * client = static_cast<QWebSocket*>(sender());
	QString tips_message;
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (clients[i] == client)
		{
			clients[i]->close();
			clients_state[i] = 0;
			current_client_num--;

			switch (i)
			{
			case 0: client1_Button->setVisible(false);
				break;
			case 1: client2_Button->setVisible(false);
				break;
			case 2: client3_Button->setVisible(false);
				break;
			case 3: client4_Button->setVisible(false);
				break;
			}
			tips_message = QString("clinet %1 is offline!").arg(i + 1);
			break;
		}
	}
	this->receive_message(tips_message);

	bool no_client_online = true;
	for (int j = 0; j < MAX_CLIENT; j++)
	{
		if (clients_state[j] == 1)
		{
			no_client_online = false;
			break;
		}
	}
	if (no_client_online == true)
	{
		this->stop_server();
	}
}

void Server::receive_client_message(QString msg)
{
	QWebSocket * client = static_cast<QWebSocket*>(sender());
	QString message_to_print;
	QString message_to_transmit;
	if (msg.mid(0, 11) == "from client")
	{
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if (clients[i] == client)
			{
				message_to_print = QString("%1---->%2").arg(i + 1).arg(msg[17]);
				message_to_transmit = msg;
				break;
			}
		}
		int client_transmit = msg[17].toLatin1() - '0';
		if (clients_state[client_transmit - 1] == 0)
		{
			this->store_message_not_transmit(message_to_transmit, client_transmit);
		}
		else
		{
			clients[client_transmit - 1]->sendTextMessage(message_to_transmit);
		}
	}
	if (msg.mid(0, 10) == "Group Chat")
	{
		message_to_print = "Group Chat message";
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			if ((clients_state[i] == 1) && (clients[i] != client))
			{
				clients[i]->sendTextMessage(msg);
			}
		}
	}
	this->receive_message(message_to_print);
}

void Server::receive_message(QString msg)
{
	receive_client_message_TextEdit->setAlignment(Qt::AlignLeft);
	receive_client_message_TextEdit->append(msg);
	if (log_write_state == true)
	{
		this->log_write(msg);
	}
}

void Server::clear_message_record()
{
	receive_client_message_TextEdit->clear();
}

void Server::store_message_not_transmit(QString msg,int client)
{
	QString file_name = QString("%1/message_not_transmit_%2.txt").arg(chat_record_Dir_path).arg(client);
	QFile file(file_name);

	if (!(file.open(QIODevice::Append | QIODevice::Text)))
	{
		this->receive_message("message_not_transmit file open failed!");
		return;
	}
	else
	{
		QTextStream outfile(&file);
		outfile << msg << endl;
	}

	file.close();
}

void Server::transmit_store_message(int client)
{
	QString file_name = QString("%1/message_not_transmit_%2.txt").arg(chat_record_Dir_path).arg(client);
	QFile file(file_name);
	if (!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
	{
		this->receive_message("store message file open failed!");
		return;
	}
	else
	{
		QTextStream infile(&file);
		QString line = infile.readLine();
		while (!line.isNull())
		{
			QString message(line);
			clients[client - 1]->sendTextMessage(message);
			line = infile.readLine();
		}
	}
	file.remove();
}

void Server::log_write(QString msg)
{
	QString log_file_name = QString("%1/server.log").arg(log_Dir_path);
	QFile file(log_file_name);
	if (!(file.open(QIODevice::Append | QIODevice::Text)))
	{
		this->receive_message("log file open failed!");
		return;
	}
	else
	{
		QTextStream outfile(&file);
		QString time = current_date_time->currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
		outfile << time << endl;
		outfile << "    " << msg << endl;
	}
	file.close();
}

void Server::log_write_state_change()
{
	log_write_state = log_write_Radiobutton->isChecked();
	if (log_write_state == true)
	{
		this->receive_message("log write is open!");
	}
	if (log_write_state == false)
	{
		this->receive_message("log write is close!");
	}
}
