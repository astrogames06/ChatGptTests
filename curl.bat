@echo off
curl https://api.openai.com/v1/images/generations -H "Content-Type: application/json" -H "Authorization: Bearer %OPENAI_API_KEY%" -d "{\"model\":\"gpt-image-1\",\"prompt\":\"A cute baby sea otter\",\"n\":1,\"size\":\"1024x1024\"}"
pause
