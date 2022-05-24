stock strfmt(dest[], const format[], size = sizeof format)
{
	dest[0] = EOS;
	strcat(dest, format, size);
	return 1;
}