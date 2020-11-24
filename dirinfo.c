#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	DIR *curr_dir;
	char file_path_and_name[150];
	//char *file_part_of_path;
	if (argc > 1)
	{
		curr_dir = opendir(argv[1]);
		strcpy(file_path_and_name, argv[1]);
	}
	else
	{
		char buffer[100];
		printf("What directory do you want read? : ");
		fgets(buffer, sizeof(buffer), stdin);
		int i = 0;
		while (buffer[i] && i < 100)
		{
			if (!('\n' - buffer[i]))
			{
				buffer[i] = 0;
			}
			i++;
		}
		//printf("Buffer: %sEND\n",buffer);
		//printf("cmp: %d\n",strcmp("./",buffer));
		curr_dir = opendir(buffer);
		strcpy(file_path_and_name, buffer);
	}

	//printf("len of dir stuffs: %lu\n",strlen(file_path_and_name));
	int path_cut = strlen(file_path_and_name);
	//curr_dir = opendir("./");

	struct dirent *entry;

	//Find
	entry = readdir(curr_dir);
	int num_dirs = 0;
	int num_files = 0;
	int file_size = 0;
	struct stat file_info;
	while (entry)
	{
		if (entry->d_type == 8)
		{
			strcat(file_path_and_name, entry->d_name);
			num_files++;
			stat(file_path_and_name, &file_info);
			file_size += file_info.st_size;
			file_path_and_name[path_cut] = 0;
		}
		else
		{
			num_dirs++;
		}
		entry = readdir(curr_dir);
	}
	rewinddir(curr_dir);
	//printf("num_files:%d\n",num_files);
	//printf("num_dirs:%d\n\n",num_dirs);

	//Assign files to file array and dirs to dir array
	char *dir_array[num_dirs];
	struct dirent *file_array[num_files];

	int d = 0;
	int f = 0;
	entry = readdir(curr_dir);
	//printf("d:%d\n",d);
	while (entry)
	{
		//printf("name:%s\ttype: %d\n",entry->d_name,entry->d_type);
		if (entry->d_type == 8)
		{
			file_array[f] = entry;
			f++;
		}
		else
		{
			//printf("name:%s\ttype: %d\n",entry->d_name,entry->d_type);
			dir_array[d] = entry->d_name;
			//printf("D: %s\n",dir_array[d]);
			d++;

			//printf("\nd:%d\n",d);
		}
		entry = readdir(curr_dir);
	}
	rewinddir(curr_dir);
	//printf("f: %d\td: %d\n",f,d);

	//Print total file size
	printf("\nTotal file size: %d\n", file_size);

	//-1 since last while loop ended after char array end
	d = d - 1;
	f = f - 1;
	//Print Files and dirs
	printf("\n");
	while (d >= 0)
	{
		printf("D: %s\n", dir_array[d]);
		d--;
	}
	printf("\n");
	while (f >= 0)
	{
		strcat(file_path_and_name, file_array[f]->d_name);
		stat(file_path_and_name, &file_info);
		file_path_and_name[path_cut] = 0;
		printf("%ld bytes - F: %s\n", file_info.st_size, file_array[f]->d_name);
		f--;
	}

	rewinddir(curr_dir);
	closedir(curr_dir);
	return 0;
}