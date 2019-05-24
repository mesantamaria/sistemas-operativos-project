#pragma once

int file_size(crFILE* file_desc);
int cr_read(crFILE* file_desc, void* buffer, int nbytes);