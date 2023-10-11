#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	int MAX_DATA;
	int MAX_ROWS;
	struct Address **rows;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void die(const char *message, struct Connection *conn)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	if (conn->db) free(conn->db);
	free(conn);
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n",
			addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	//int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	//if(rc != 1) die("Failed to load database.", conn);
	int rc = fread(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to load MAX_DATA", conn);
	rc = fread(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
	if (rc != 1) die("Failed to load MAX_ROWS", conn);
	
	// 要为 rows 分配内存
	
	conn->db->rows = malloc(conn->db->MAX_ROWS * sizeof(struct Address*));

	for (int i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *addr = malloc(sizeof(struct Address));
		rc = fread(&addr->id, sizeof(int), 1, conn->file);
		if (rc != 1) die("Failed to load id", conn);
		rc = fread(&addr->set, sizeof(int), 1, conn->file);
		if (rc != 1) die("Failed to load set", conn);
		addr->name = malloc(conn->db->MAX_DATA);
		rc = fread(addr->name, sizeof(char), conn->db->MAX_DATA, conn->file);
		if (rc != conn->db->MAX_DATA) die("Failed to load name", conn);
		addr->email = malloc(conn->db->MAX_DATA);
		rc = fread(addr->email, sizeof(char), conn->db->MAX_DATA, conn->file);
		if (rc != conn->db->MAX_DATA) die("Failed to load email", conn);
		conn->db->rows[i] = addr;
	}
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if (!conn->db) die("Memory error", conn);

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file", conn);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);
	
	int rc = fwrite(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
	if(rc != 1) die("Failed to write maxdata", conn);
	rc = fwrite(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
       	if(rc != 1) die("Failed to write maxrows", conn);
	for(int i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *addr = conn->db->rows[i];
		rc = fwrite(&addr->id, sizeof(int), 1, conn->file);
		if (rc != 1) die("Failed to write id", conn);
		rc = fwrite(&addr->set, sizeof(int), 1, conn->file);
		if (rc != 1) die("Failed to write set", conn);
		rc = fwrite(addr->name, sizeof(char), conn->db->MAX_DATA, conn->file);
		if (rc != conn->db->MAX_DATA) die("Failed to write name", conn);
		rc = fwrite(addr->email, sizeof(char), conn->db->MAX_DATA, conn->file);
		if (rc != conn->db->MAX_DATA) die("Failed to write email", conn);
	}	

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int max_data, int max_rows)
{
	conn->db->MAX_DATA = max_data;
	conn->db->MAX_ROWS = max_rows;
	conn->db->rows = malloc(max_rows * sizeof(struct Address*));
	int i = 0;

	for(i = 0; i < max_rows; i++) {
		struct Address *addr = malloc(sizeof(struct Address));
		addr->id = i; 
		addr->set = 0;
		addr->name = malloc(max_data);
		addr->email = malloc(max_data);
		memset(addr->name, '\0', max_data);
		memset(addr->email, '\0', max_data);
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = conn->db->rows[id];
	Address_print(addr);
	if(addr->set) die("Already set, delete it first", conn);

	addr->set = 1;
	// bug, read how to break it and fix this
	char *res = strncpy(addr->name, name, conn->db->MAX_DATA);
	if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];
	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	conn->db->rows[id]->set = 0;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < conn->db->MAX_ROWS; i++) {
		struct Address *cur = db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 5) die("USAGE: ex17 <dbfile> <max_data> <max_rows> <action> [action params]", NULL);

	char *filename = argv[1];
	char action = argv[4][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc > 5) id = atoi(argv[5]);
	if(id >= atoi(argv[3])) die("There is not that many records.", conn);

	switch(action) {
		case 'c':
			if(argc != 5) die("Need max_data and max_rows", conn);
			Database_create(conn, atoi(argv[2]), atoi(argv[3]));
			Database_write(conn);
			break;

		case 'g':
			if(argc != 6) die("Need an id to get", conn);

			Database_get(conn, id);
			break;

		case 's':
			if(argc != 8) die("Need id, name, email to set", conn);

			Database_set(conn, id, argv[6], argv[7]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 6) die("Need id to delete", conn);

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
	}

	Database_close(conn);

	return 0;
}

