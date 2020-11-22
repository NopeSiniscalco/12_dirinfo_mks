#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	DIR *curr_dir;
	curr_dir = opendir("./");

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
			num_files++;
			stat(entry->d_name, &file_info);
			file_size += file_info.st_size;
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
	char *file_array[num_files];

	int d = 0;
	int f = 0;
	entry = readdir(curr_dir);
	//printf("d:%d\n",d);
	while (entry)
	{
		//printf("name:%s\ttype: %d\n",entry->d_name,entry->d_type);
		if (entry->d_type == 8)
		{
			file_array[f] = entry->d_name;
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
	printf("\nTotal file size: %d\n",file_size);



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
		printf("F: %s\n", file_array[f]);
		f--;
	}

	/*
	entry = readdir(curr_dir);
	while (entry)
	{
		printf("Type:%d\tName: %s\n", entry->d_type, entry->d_name);
		entry = readdir(curr_dir);
	}
	*/

	rewinddir(curr_dir);
	closedir(curr_dir);
	return 0;
}