import subprocess

def lambda_handler(event, context):
	print(subprocess.check_output(['./test']))
